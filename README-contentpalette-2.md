# Scribus Content palette

Second try at creating a Content palette with

- Text properties
- Image properties
- Group properties
- ...

## Implementation

- [x] Create a new Content Palette of type `ScDockPalette`.
- [x] Add the content palette to `scribus.cpp`.
  - search for:
    - [x] `propertiesPalette -> contentpalette`
    - [x] `PAL_PROPERTIES -> PAL_CONTENT`
      - `scribusstruct.h`
    - [x] `toolsProperties -> toolsContent`
      - `actionmanager.cpp`
        `ui/contextmenu.cpp`
  - eventually add `setDoc` and  `unsetDoc` if it's useful.
  - eventually add `unitChange()` if it's useful.
  - [ ] correctly pass `languageChange()` to the real widgets
- [x] Add a `QStackedWidget` into the content palette
- [x] Add the text properties to the Stacked Widget from `scribus.cpp`
- [ ] Create a new Image Properties in the same way as the Text Properties
  - create `ui/imagepalette.h`, `ui/imagepalette.cpp` base on `ui/textpalette.*`
    - We need `setDoc()`, because it's the place where `handleSelectionChanged` is _connected_, which, then calls `setCurrentItem`.
    - it's `TextPalette::setCurrentItem()` that calls `textPal->handleSelectionChanged()`.
  - [ ] implement `setDoc()`, `handleSelectionChanged`, `setCurrentItem()`, `updateColorList()`, `languageChange` in the same way as it isi nthe textpalette.
    - Check if we can proxy to contentPalette the calls to `updateColorList` (and language change) for image and text. (making `scribus.cpp` slightly slimmer)
      - move the image palette initialization from `propertiesPalette` to `contentPalette`
      - move the text palette initialization from `scribus.cpp` to `contentPalette` (cf. image in pp)
  - `scribus.cpp`
    - [ ] `textPalette -> imagePalette` (active task)
    - [ ] `toolsText -> toolsImage`
- [ ] Restart the process:
  - remove `textpalette.h|cpp` and `imagepalette.h|cpp` and directly call `propertiespalette_image` and `propertiespalette_text` from the content palette.
  - reshape the content palette to follow the structure of the properties palette.
  - remove all references to toolsText in `actionmanager.cpp`

Todo:

- [ ] remove the textpalette.h|cpp and imagepalette.h|cpp
- [ ] Change the title of the content palette according to the what is selected (Content Properties, Text Properties, Image Properties)
- [ ] What to put in the empty pane? (keep an empty one when no files are selected... or even then...)
- [ ] Move to the empty pane when selecting a table (or another "unsupported" item)
- [ ] Rename "Group" in the PP to "Shape" or "Group Shape" and only show one of "Shape" and "Group" according to the selection.
- [ ] Store the state (expanded or not) of the tabs in the text pane.
... and implement the new tab of the font prefs with the rejected fonts...
