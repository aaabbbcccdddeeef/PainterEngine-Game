$index=0
for($index=1;$index -le 3;$index++)
{
 .\PainterEngine_PngToTRaw.exe ".\$index.png" ".\$index.traw"
}

.\PainterEngine_2dxMakeTool.exe .\makefile.txt .\release.2dx