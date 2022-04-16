# Magnetic Chaos Drives
This mod makes Chaos Drives attracted to players close by.

## How to install

You need the [SA2 Mod Loader](https://github.com/X-Hax/sa2-mod-loader) to install this mod.

Download the latest version from the release page, then extract the root folder in the archive into the "mods" folder. Make sure you do not extract the individual files in the mods folder, they should be in a subfolder.

## How to configure

You can configure the mod in the Mod Manager by clicking on the mod, then on the "configure" button.

Alternatively, you can create a "config.ini" file in the mod's folder and fill in the configuration manually. Here is the list of parameters with their default values:

```
MagneticShieldCdt=False
DisableYellow=False
DisableGreen=False
DisableRed=False
DisablePurple=False
[Physics]
Radius=100
Force=1,75
MaxSpeed=50
```

## How to build

By default this project and its submodules are using the Windows 7.0 SDK and the Visual Studio 2017 XP toolkit (v141xp.) With these prerequisites, you can simply open the solution in Visual Studio and build it.

## Copyright

Certain elements used are reversed-engineered from Sonic Adventure 2: Battle © SEGA/SONIC TEAM.
