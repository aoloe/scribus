# Add the vertical swap

... and eventually fix the way swap left / right currently works.

https://bugs.scribus.net/view.php?id=15205

## Status

- the new buttons are clickable in the UI
- `scribusdoc.cpp` contains `itemSelection_SwapLeft()` and `itemSelection_SwapRight()` which are to 90% the same (or even 99%).  
  Before adding new two new functions I'd like to refactor (and understand!) the two existing functions.
  - The diff is here: <http://www.mergely.com/q71dIT9I/>
  - I've already created the empty `itemSelection_SwapHorizontally()` and `itemSelection_SwapVertically()`... but I'm not sure, it's the good approach.
- Refactoring `itemSelection_SwapLeft()` / `itemSelection_SwapRight()`... what they do:
  - If the right dialog is not open, abort (I think...)
  - Create a map of items with `x1` as the key and the index in the selected objects as the value.
  - Sort the map by the key
  - Create a map of items with `y1` as the key and the index in the selected objects as the value.
  - Sort the map by the key
  - ...
