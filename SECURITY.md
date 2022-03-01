# Concord Cybersecurity Policy

## Covered Versions
Only the latest Concord versioned release will receive security fixes. 
No older versions fall under this requirement.

## How Security Patches Are Implemented
All security patches will be applied to the `dev` branch of the repository.
To install these patches, simply clone the source code, `git checkout dev`, and
compile as normal. Please note that `dev` might contain some breaking changes.
It is advised that you do NOT attempt to manually backport fixes to older
Concord releases, as your bot will eventually become inoperable due to old
library age. 

## Reporting A Security Issue (Vulnerability)
If you come across a serious security issue, please file an issue request.
Pull requests for security fixes will be examined in great detail.
Alternatively, you can join the Discord chat as linked in the README file
if you'd like to have one-on-one conversations with the Concord developers.
