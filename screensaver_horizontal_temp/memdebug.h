int freeRAM()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void printFreeRAM(const __FlashStringHelper *message)
{
    char *textBuffer = new char[30];
    sprintf_P(textBuffer, (PGM_P)message, freeRAM());
    Serial.println(textBuffer);
    delete textBuffer;
}
