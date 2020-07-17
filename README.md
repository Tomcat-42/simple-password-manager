# simple-password-manager

This is a simple (as the name suggests) and secure password manager written in c that
store data in a single [JSON](https://json.org) file encrypted/decrypted by [gnupg](https://gnupg.org/).

## Installation

If you don't have gnupg installed, install it:

```bash
# On arch based distros:
pacman -S gnupg
```

```bash
# On debian based distros:
apt install gnupg
```

**OBS**: gnupg *must* be in `$PATH` as `gpg`;

And if you don't have a keypair, generate one:

```bash
gpg --full-gen-key
```

To view keys fingerprint:

```bash
gpg --list-keys <YOUR NAME OR EMAIL>
```

Next, edit `src/config.h`'s `PASSWORD_FILE` and `GPG_RECIPIENT` macros to specify, respectively, the absolute file path where passwords will be stored and the 40 digit hexadecimal fingerprint of your public key.

Finally, compile and install:

```bash
make && sudo make install
```

**OBS**: `make install` will copy `spm` and `spm-dmenu` to `/usr/bin` by default, if you want to change installation target edit `config.mk` (or just `make` and do whatever you want with `spm` and `spm-dmenu`).

## Usage

Each entry have 4 fields: *name*, *login*, *password* and *other*, in which only *name* and *login* are mandatory. 

Add a entry:
```bash
spm -a|--add name login [password] [other]
```

Show a entry by name:
```bash
spm -s|--show name
```

Delete a entry by name:
```bash
spm -d|--delete name
```

List all entries:
```bash
spm -l|--list
```

Help:
```bash
spm -h|--help
```

## spm-dmenu

`spm-dmenu` is a wrapper script for `spm` that uses [dmenu](https://tools.suckless.org/dmenu/) for navigation and  [xsel](https://linux.die.net/man/1/xsel) for copyind data to clipboard.

Install dmenu and xsel:

```bash
# On arch based distros:
pacman -S xsel dmenu
```

```bash
# On debian based distros:
apt install xsel dmenu
```

Run the script(or configure a key binding):

```bash
./spm-dmenu
```


<img src="https://media.giphy.com/media/J6CZ1qPSPzQDYnJlCq/giphy.gif" width=100% />
