' Change the Windows Power Plan to a named plan 
' Name your plan 
     strPowerPlan="High performance" ' This is not case sensitive 
' Get WMI object under power 
     Set objWMI = GetObject("winmgmts:\\.\root\cimv2\power")  
' Do a search for the named power management plan 
     Set colPlans = objWMI.ExecQuery("Select * From Win32_PowerPlan where ElementName='"&strPowerPlan&"'")  
' A collection is returned which should only contain one item. 
     For Each objPlan In colPlans 
' Activate the plan 
        objPlan.Activate() 
     next