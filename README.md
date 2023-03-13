# suns map

This is a headless OpenFrameworks application, hosed on a DO droplet, which draws an image based on a remote input

## architecture

First, the web server has the `/post` endpoint, which parses an array of comma-separated values including:

- generation of the entrypoint
- status of the entrypoint (open, pending, completed)
- cluster (name)
- lat (floating point number)
- lng (floating point number)

From this request, a series of markers are created from scratch and passed to the `Map` object.

How each marker is drawn is decided in `Marker.cpp`, wtih three main variables:

- the shape represents the cluser
- the color represents the status
- the size represents the generation

## notes

because OF requires a GL context, and running an app headless does not have one, we have to run the app in production with:

`/usr/bin/xvfb-run -a /root/of_v20221126_linux64gcc6_release/apps/myApps/suns-map/bin/suns-map`

## environment

- `PROD` and `DEV` essentially decide where the images should be saved.
