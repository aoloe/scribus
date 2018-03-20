# Scribus content palette

A content palette that shows the text, image, line or group palette depending on the type of selection.

The palette is a `QStackedWidget` and the code has been cloned from the existing text palette files.

Further ideas:

- If we want to pick a palette in multiple selections or groups, we can add a widget between the content palette and the selection / group palette: a vertical layout with buttons on top and the palette at the bottom.

## Notes

- http://doc.qt.io/qt-5/qstackedwidget.html
