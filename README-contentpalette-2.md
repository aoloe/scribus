# Scribus Content palette

Second try at creating a Content palette with

- Text properties
- Image properties
- Group properties
- ...

## Implementation

- [x] Create a new Content Palette of type `ScDockPalette`.
- [x] Add the content palette to `scribus.cpp`. (current task)
  - search for:
    - [x] `propertiesPalette -> contentpalette`
    - [x] `PAL_PROPERTIES -> PAL_CONTENT`
      - `scribusstruct.h`
    - [x] `toolsProperties -> toolsContent`
      - `actionmanager.cpp`
        `ui/contextmenu.cpp`
  - eventually add `setDoc` and  `unsetDoc` if it's useful.
  - eventually add `unitChange()` if it's useful.
- [x] Add a `QStackedWidget` into the content palette
- [x] Add the text properties to the Stacked Widget from `scribus.cpp`
- [ ] Create a new Image Properties in the same way as the Text Properties
  - create `ui/imagepalette.h`, `ui/imagepalette.cpp` base on `ui/textpalette.*`
  - `scribus.cpp`
    - [ ] `textPalette -> imagePalette` (active task)
    - [ ] `toolsText -> toolsImage`
- [ ] Add the Image properteis to the Content palette.
- [ ] Move the Image tab to the Image Properties.
- [ ] Check if i can make the palette a simple widget instead of `ScDockPalette`.
- [ ] Move to moder signals and slots?
- [ ] Group
- [ ] Table?
