#pragma once
#ifndef PATTERN_SCANNER_H
#define PATTERN_SCANNER_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>
#include <string>
#include <process.h>
#include <vector>
#include <format>
#include <Psapi.h>
#include <sstream>
#include <array>


namespace PatternScanner
{
    enum PatternType
    {
        ADDRESS = 1,
        OFFSET = 2,
        VALUE = 3,
        FUNCTION_CALL = 4,
        FUNCTION = 5,
        VALUE_REF = 6,
        VALUE_BYTE = 7,
        OFFSET_BYTE = 8,
        VALUE_REF_BYTE = 9
    };

    template<std::size_t SIZE>
    struct Pattern;

    template <std::size_t SIZE>
    DWORD64 AddressLookup(DWORD64 startAddress, DWORD64 endAddress, Pattern<SIZE> pattern) {
        for (DWORD64 address = startAddress; address <= endAddress; address += 0x1) {
            for (BYTE offset = 0; offset < pattern.rawPattern.size(); offset++) {
                if (pattern.rawPattern[offset] == 0x0) continue;    // 0x0 means blank '?', skipping it
                if (*(BYTE*)(address + offset) != pattern.rawPattern[offset]) break;
                if (offset == pattern.rawPattern.size() - 1) return address + pattern.offset;
            }
        }
        return 0x0;
    }

    constexpr size_t bytesAmount(const std::string_view& str, size_t count = 1) {
        return (str.empty()) ? count :
            bytesAmount(str.substr(1), count + ((str[0] == ' ') ? 1 : 0));
    }

    inline char ToLower(char c) {
        return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
    }

    inline BYTE charToHexNumber(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return 10 + c - 'a';
        return 0; // Ideally, handle this case more robustly
    }

    inline BYTE hexCharToByte(char c) {
        c = ToLower(c);
        return charToHexNumber(c);
    }

    template <std::size_t SIZE>
    std::array<BYTE, SIZE> convertStringToBytes(const std::string_view& byteString) {
        std::array<BYTE, SIZE> bytes{};
        std::size_t index = 0;

        for (std::size_t i = 0; i < byteString.size() && index < SIZE;) {
            if (byteString[i] == '?') {
                bytes[index++] = 0x0;   // In IDA style pattern '?' means blank, treating it as 0x0
                ++i;
            }
            else if (byteString[i] != ' ') {
                if (i + 1 < byteString.size()) {
                    BYTE nibble1 = hexCharToByte(byteString[i]);
                    BYTE nibble2 = hexCharToByte(byteString[i + 1]);
                    bytes[index++] = (nibble1 << 4) | nibble2;
                    i += 2; // Skip next character as it is part of the current byte
                }
            }
            else {
                ++i; // Skip spaces
            }
        }

        return bytes;
    }

    template<std::size_t SIZE>
    struct Pattern
    {
        Pattern(const std::string_view& stringPattern, DWORD64 offset, PatternType type) {
            rawPattern = convertStringToBytes<SIZE>(stringPattern);
            this->offset = offset;
            this->type = type;
        }

        PatternType type;
        DWORD64 offset = 0x0;
        std::array<BYTE, SIZE> rawPattern;
    };

    static IMAGE_SECTION_HEADER* GetModuleTextSection(DWORD64 baseModule) {
        IMAGE_DOS_HEADER* dosHeader = (PIMAGE_DOS_HEADER)baseModule;
        auto* ntHeaders = (PIMAGE_NT_HEADERS)(baseModule + dosHeader->e_lfanew);
        auto* textSection = IMAGE_FIRST_SECTION(ntHeaders);

        return textSection;
    }

    template<std::size_t SIZE>
    DWORD64 FindPattern(Pattern<SIZE> pattern, const char* module_name) {
        DWORD64 moduleAddress = (DWORD64)GetModuleHandleA(module_name);
        auto textSection = GetModuleTextSection(moduleAddress);

        DWORD64 realAddress = AddressLookup<pattern.rawPattern.size()>((DWORD64)textSection, (DWORD64)textSection + (DWORD64)textSection->SizeOfRawData, pattern);

        if (realAddress == 0x0)
            return 0x0;

        DWORD64 offset = realAddress - pattern.offset;
        switch (pattern.type)
        {
        case PatternType::ADDRESS:
            return offset;
        case PatternType::VALUE:
            return *(DWORD*)(realAddress);
        case PatternType::VALUE_BYTE:
            return *(BYTE*)(realAddress);
        case PatternType::VALUE_REF:
            return *(DWORD*)(moduleAddress + (DWORD)(realAddress - moduleAddress + *(DWORD*)(offset + 0x1) + 0x5));
        case PatternType::VALUE_REF_BYTE:
            return *(BYTE*)(moduleAddress + (DWORD)(realAddress - moduleAddress + *(DWORD*)(offset + 0x1) + 0x5));
        case PatternType::OFFSET:
            return offset - moduleAddress + *(DWORD*)(realAddress) + 0x4 + pattern.offset;
        case PatternType::OFFSET_BYTE:
            return offset - moduleAddress + *(DWORD*)realAddress + 0x5 + pattern.offset;
        case PatternType::FUNCTION:
            return offset - moduleAddress + pattern.offset;
        case PatternType::FUNCTION_CALL:
            return DWORD(realAddress - moduleAddress + *(DWORD*)(realAddress + pattern.offset + 0x1) + 0x5);
        default:
            return 0x0;
        }
    }

    #define CREATE_PATTERN(pattern, offset, type) Pattern<PatternScanner::bytesAmount(pattern)>(pattern, offset, type)
}
#endif