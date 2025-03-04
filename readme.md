<!-- 2025.1.673329 -->


<h1 align="center">
  <br>
  <a href="https://github.com/emayolle/logitech-ghub-api-extender"><img src="https://www.logitechg.com/content/dam/logitech/en/nav/brand-logos/new/logitech.svg" alt="logitech-ghub-api-extender" width="300"></a>
  <br>
  Logitech G-HUB Lua API Extender
  <br>
</h1>

<h4 align="center">A library extender of the Lua API for <code>Logitech HUB</code> engine, that allows a user to create his own Lua CFunction / logic integration.</h4>


<p align="center">
  <a href="#context">Context</a> •
  <a href="#key-features">Key Features</a> •
  <a href="#todo-list">Todo List</a> •
  <a href="#installation">Installation</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#credits">Credits</a> •
  <a href="#license">License</a>
</p>

<!-- ![screenshot](https://raw.githubusercontent.com/emayolle/django_final/main/git_images/exemple.gif) -->

> **Note**
> Support version **__2025.1.673329__** of LGHub

## Context
The [Logitech Hub](https://www.logitechg.com/fr-fr/innovation/g-hub.html) is an application platform designed to integrate various [Logitech devices](https://www.logitechg.com/), offering a centralized control interface for users to manage their connected hardware. This includes devices like keyboards, mice, speakers, and more, allowing for streamlined interaction and automation.

The [Lua](https://www.lua.org/) API provided by the Logitech Hub is a powerful tool that enables programmable control over these devices using the Lua scripting language. Every G-series Profile has a default Lua script bound to it which can be edited and customized.
The script is invoked using an event handler, OnEvent. Users may examine the various events
exposed in this handler to perform their desired actions.

The Lua version used is [Lua 5.4](https://www.lua.org/versions.html#5.4) with methods or functions added by the Logitech Hub API.

> **Note**
> Logitech Lua API can be found on [this page](https://douile.com/logitech-toggle-keys/APIDocs.pdf).
## Key Features

* Integrate custom Lua C Function
  - The user will be able to bound his own C function to the Lua enviroment.



## Todo List

- [x] Hook LuaVM
- [x] Add Pattern Matching to make auto-update of offsets
- [x] Integrate Lua C API
- [ ] Documentation of the project

## Installation
To clone and run this application, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. Once you have CMake installed, you can clone the project using the following command:
```bash
cmake .
```
Then, you need to build the project using the following command:
```bash
cmake --build .
```

## How To Use

<!-- To use the project, you need to run `build/LGPro.exe`. -->
To use the project, you need to have a DLL Injector to inject the `build/LGProLib.dll` in the process name `lghub_agent.exe`.

> **Note**
> You can also use [Process Hacker](https://processhacker.sourceforge.io/downloads.php), right-click on the process, and select "Miscellaneous > Inject DLL" to inject the DLL.


<!-- 
> **Note**
> If you're using Linux Bash you can do `python manage.py shell < generate_data.py` to generate some data in the database.
-->

## Credits

- Application created by [Erwan Mayolle](https://github.com/emayolle).
- This readme is using the template created by [amitmerchant1990](https://github.com/amitmerchant1990).

## License

MIT

---

> GitHub [@emayolle](https://github.com/emayolle)

