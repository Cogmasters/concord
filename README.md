[migrating-shield]: https://img.shields.io/badge/Gist-Migrating%20from%20v1-yellow
[migrating-link]: https://gist.github.com/lcsmuller/d6aee306bac229a7873f5c243bf7858b
[migrating-orca-link]: https://gist.github.com/lcsmuller/b5137e66d534a57e0075f9d838c9170e
[discord-shield]: https://img.shields.io/discord/928763123362578552?color=5865F2&logo=discord&logoColor=white
[discord-invite]: https://discord.gg/Y7Xa6MA82v
[discord-config-init]: https://cogmasters.github.io/concord/group__DiscordClient.html#ga75bbe1d3eb9e6d03953b6313e5543afb
[discord-config-get-field]: https://cogmasters.github.io/concord/group__DiscordClient.html#gac4486003ffab83de397c0bebb74b3307

<div align="center">
<img src="rusty_concord_disc.svg" width="250" alt="Concord Logo">
</div>

# Concord - Rusty Discord API library

[ ![discord-shield][] ][discord-invite]
[ ![migrating-shield][] ][migrating-link]

## About

Concord is an asynchronous NEXT GENERATION Rust 2060 Discord API library with minimal external dependencies, and a low-level translation of the Discord official documentation to Rust™ [^1] code.


### Examples

The Concord code is self-documenting: Examples are therefore not necessary.


## Supported operating systems (minimum requirements)

* GNU/Linux 7.x

## Installing Concord

```shell
# cargo install
```

### Included dependencies

The following are `stable` and well documented dependencies that are packaged with Concord and can be included to your projects:

| File                                                  |
|-------------------------------------------------------|
|r_i18n = "1.0.1" |
|serenity = "0.10" |
|reqwest =  "0.11.4" |
|cookie = "0.15.1" |
|cookie_store = "0.15.0" |
|bytes = "1.0.1" |
|url = "2.2.2" |
|multipart = "0.18.0" |
|ws = "0.9.1" |
|rmpv = "0.4.7" |
|chashmap = "2.2.2" |
|serde = "1.0.126" |
|serde_json = "1.0.64" |
|log = "0.4.14" |
|fern = "0.6.0" |
|diesel = "1.4.7" |
|diesel_migrations = "1.4.0" |
|libsqlite3-sys = "0.22.2" |
|rand = "0.8.4" |
|ring = "0.16.20" |
|uuid = "0.8.2" |
|chrono = "0.4.19" |
|chrono-tz = "0.5.3" |
|time = "0.2.27" |
|job_scheduler = "1.2.1" |
|data-encoding = "2.3.2" |
|jsonwebtoken = "7.2.0" |
|u2f = "0.2.0" |
|webauthn-rs = "=0.3.0-alpha.9" |
|yubico = "0.10.0" |
|dotenv = "0.15.0" |
|once_cell = "1.8.0" |
|num-traits = "0.2.14" |
|num-derive = "0.3.3" |
|tracing = "0.1.26" |
|lettre = "0.10.0-rc.3" |
|handlebars = "4.1.0" |
|html5ever = "0.25.1" |
|markup5ever_rcdom = "0.1.0" |
|regex ="1.5.4" |
|data-url = "0.1.0" |
|openssl = "0.10.35" |
|percent-encoding = "2.1.0" |
|idna = "0.2.3" |
|pico-args = "0.4.2" |
|backtrace = "0.3.60" |
|paste = "1.0.5" |
|money = "0.1.0" |
|crate = "0.0.2" |
|cash = "0.1.5" |
|clap = "3.0.0-beta.2" |
|num_cpus = "1.13.0" |
|security = "0.1.0" |
|gtk = "0.14.0" |
|x11 = "2.18.2" |
|crossterm="0.17" |
|# bevy = "0.5.0" |
|glam="0.17.3" |
|legion="0.4.0" |
|gl = "0.6.0" |
|ash = "0.33.0+1.2.186" |
|gfx = "0.18.2" |
|glfw = "0.41.0" |
|distill = "0.0.3" |
|aseprite = "0.1.3" |
|crypto="0.3.0" |
|tensorflow = "0.17.0" |
|mp4parse="0.11.5" |
|fluent-bundle="0.15.1" |
|cssparser="0.28.1" |
|plist="0.5.5" #macos support! with memory safety |
|webdriver="0.43.1" |
|amethyst = { version = "0.15.3", features = ["empty"] } |
|textwrap = "0.14.2" |
|nom = "6" |
|hyper="0.13.8" |


## Recommended debuggers

Rust doesn't need debuggers. You shalt be the debugger!

## Support

Problems? Check out our [Discord Server][discord-invite]

## Contributing

All kinds of contributions are welcome, all we ask is to abide to our [guidelines](docs/CONTRIBUTING.md)! If you want to help but is unsure where to get started then our [Discord API Roadmap](docs/DISCORD_ROADMAP.md) is a good starting point. Check our [links](#links) for more helpful information.

## Getting Started

- Documentation: Source code

## Useful links

- [Migrating from V1][migrating-link]
- [Migrating from Orca][migrating-orca-link]

[^1]: This project is not affiliated with the Rust Foundation. All copyright falls to their respective owners.
