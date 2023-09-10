# Starboard bot clone in Concord

## How to make and run
### Make it
> Don't forget to put your Discord User ID in `src/config.h` before making !!!

Keep in mind, that you should be running this from the `examples/` folder
```sh
make starboard
cd starboard_clone
```
### Run it
```
./sbclone
```

## Okay, I did that, what's next
### Adding channels
#### First, add a board channel
```
/add channel: #board isboard: true
```
#### Second, add as much submission channels as you want
```
/add channel: #general isboard: false
/add channel: #memes isboard: false
...
```
You're all set now!
