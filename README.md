# Magnetic Chaos Drives
This mod makes Chaos Drives attracted to the closest player in a certain radius.

## How to install

You need the [SA2 Mod Loader](https://github.com/X-Hax/sa2-mod-loader) to install this mod.

Download the mod on its [gamebanana page](https://gamebanana.com/mods/331757), extract the content of the archive in the "mods" folder. Alternatively, you can install the URL handler in the Mod Manager options to use GameBanana's automatic install.

## How to configure the mod

You can configure the mod in the Mod Manager by clicking on the mod, and then on the "configure" button.

Alternatively, you can create a "config.ini" file at the root of the mod and fill in the configuration manually. Here is the list of parameters with their default values:

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
