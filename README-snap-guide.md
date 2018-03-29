# snap guides to items

when the shift key is down, moving a guide should snap to the items.

the works seems to be done in `canvasgesture_rulermove.cpp`

`canvasmode_normal.cpp` is also of some interest.

```cpp
if (!m_guideMoveGesture)
{
    m_guideMoveGesture = new RulerGesture(m_view, RulerGesture::HORIZONTAL);
    connect(m_guideMoveGesture, SIGNAL(guideInfo(int,qreal)), m_ScMW->alignDistributePalette, SLOT(setGuide(int,qreal)));
}
if ( (!m_doc->GuideLock) && (m_guideMoveGesture->mouseHitsGuide(mousePointDoc)) )
{
    m_view->startGesture(m_guideMoveGesture);
    m_guideMoveGesture->mouseMoveEvent(m);
    m_doc->m_Selection->connectItemToGUI();
    return true;
}
```
