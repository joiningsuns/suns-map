# suns map

a map that develops over time and generations of entrypoints. can also be subjected to sacrifices.

## todo

- [x] stop the draw loop once it's printed
- [x] display shapes several time for one marker, based on how old it is
- [ ] figure out how to not clear the markers, and update the markers that are already existing
- [ ] draw paths between markers
- [ ] show only outline if open, filled if pending, filled and thick outline if completed
- [ ] figure out a background (districts could be patterns: just `* * *` or `( ) ( ) ( )`)
- [x] fix the issue where only top left quarter of markers is displayed

- having 2 or 3 Path typologies (hand drawn, parallel lines)
- having a grid of points in the background
- changing the icons in the middle (with a simple cross)

## palettes

- https://colorswall.com/palette/178942
- https://colorkit.co/palette/ab5852-eadaa0-d69e49-838469-476066/

## factors

data which should be provided as comma-separated values
- generation
- status
    - open: just filled?
    - pending: filled + stroke (stroke style: dotted vs. line)
    - done: desaturated
- cluster
- lat
- lng

## notes

inspired by [kevin lynch's image of the city](https://en.wikipedia.org/wiki/The_Image_of_the_City)

- __variables__
    - generation
    - cluster
    - status

- __static elements__
    - district
        - ofShape() with some randomized vertices, and a bit of alpha
        - 3d surface
        - heightmap
        - topography lines shader
        - move all vertices in a given area to smooth slope
    - path
        - randomize whether the path is drawn or not
        - draw from entrypoint OR from average mean of entrypoint
        - branch away from path?
    - edge
        - limit of zone of influence of each entrypoint?
    - node
        - entrypoints, could have specific addition to it (already done)
    - landmark
        - tbd but needed (lake?)
        - squares as houses
        
- __modes of interaction__
    - proximity?
    - similar clusters?
        
        
- __file input/output__
    - command line args
    - take input coordinates between [[0,0], [500,500]], with a type, and a status (for now, as JSON)
    - affect a radius around each input
    - write image that's 1000x1000

- __http server__
