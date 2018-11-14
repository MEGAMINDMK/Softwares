
' InputBoxes

Message = InputBox("What Is The Message?","Facebook DDos")

'MsgBox "VBScript Written By M Raahim Khattak"

T = InputBox("How Many Times Needs It To Be Send?","Facebook DDos")

If MsgBox("You've Filled It In Correctely", 1024 + vbSystemModal, "Facebook DDos") = vbOk Then



' Go To Facebook

Set WshShell = WScript.CreateObject("WScript.Shell")

Return = WshShell.Run("https://www.facebook.com/messages/t/azan.ali.756", 1)



' Loading Time



If MsgBox("Search for the name and click on message section?" & vbNewLine & vbNewLine & "Press No To Cancel", vbYesNo + vbQuestion + vbSystemModal, "Facebook DDos") = vbYes Then



' The Loop For The Messages

For i = 0 to T

WScript.Sleep 5

WshShell.SendKeys Message

WScript.Sleep 5

WshShell.SendKeys "{ENTER}"

Next



' End Of The Script

WScript.Sleep 3000

MsgBox "Please Visit www.youtube.com/channel/UC2eTGoGsnz0sg7VDcBZggNQ"

Set WshShell = WScript.CreateObject("WScript.Shell")

Return = WshShell.Run("https://www.youtube.com/channel/UC2eTGoGsnz0sg7VDcBZggNQ", 1)





' Canceled Script

Else

MsgBox "Process Has Been Canceled", vbSystemModal, "DDos Canceled"

End If

Else

End If