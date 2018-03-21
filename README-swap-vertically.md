# Add the vertical swap

... and eventually fix the way swap left / right currently works.

https://bugs.scribus.net/view.php?id=15205

the original ticket, after which it has been implemented:  
https://bugs.scribus.net/view.php?id=480

## Status

- the new buttons are clickable in the UI
- `scribusdoc.cpp` contains `itemSelection_SwapLeft()` and `itemSelection_SwapRight()` which are to 90% the same (or even 99%).  
  Before adding new two new functions I'd like to refactor (and understand!) the two existing functions.
  - The diff is here: <http://www.mergely.com/q71dIT9I/>
  - I've already created the empty `itemSelection_SwapHorizontally()` and `itemSelection_SwapVertically()`... but I'm not sure, it's the good approach.
- Refactoring `itemSelection_SwapLeft()` / `itemSelection_SwapRight()`... what they do:
  - If the right dialog is not open, abort (I think...)
  - Create a map of items with `x1` as the key and the index in the selected objects as the value. (items with the same `x1` "get lost")
  - find the min and max x1 value (`minX`, `maxX`)
  - Create a map of items with `y1` in the same way as for `x1`
  - The map is automatically sorted
  - find the min and max y1 value (`minY`, `maxY`)
  - overwrite `minY` and `maxY` with the min and max doubles
  - create a circleList (`QList<int>`)
  - add the first item sorted by y (`itX`) to the circleList.
  - set the circleListCounter to 1
  - add to circleList the index of each item with an `y1` smaller than the `y1` of the first item (the one with the smallest `x1`)
  - add to circleList the index of each item, looped backwards from the last item, with an `y1` bigger or equal than the `y1` of the first item (the one with the smallest `x1`)
  - at the end `circleListCounter` is probably equal to the number of items.
  - keep the the x and y of the first item in the selection as swapX and swapY.
  - move each `Object` in the first `AObject` by the difference between the `x1` of the last AObject minus the `x1` of the first AObject; and do the same for `y1`
  - do the same for all the other AObjects
  move all Objects of the last AObjects by the difference between the x1 of the former first AObjects and x1 of the current last AObjects.
    

refactoring?

- AlignObjs is built in `buildAlignItemList()` for the `PageItem*` in the selection.
- AlignObjs.Objects seems to always contain one single `PageItem*`.
- in AlignObjs, only x1, y1, x2, y2 are used (the other fields are not set or never used) --> not true width is in use...
- QObjects should be one single `PageItem*` not a list.
- We can probably directly use PageItems and remove the AlignObjs struct. Each function must then call  
  `currItem->getBoundingRect(&Object.x1, &Object.y1, &Object.x2, &Object.y2);`


The feature:

- when you take two items of different size, the effect is very strange.
- inkscape use the center of the shape as a reference. and it looks a bit better.
