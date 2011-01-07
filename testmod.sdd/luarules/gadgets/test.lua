-- warning, don't edit this file, it will be overwritten!
function gadget:GetInfo()
return {
	name    = "Test-Gadget",
	desc    = "Runs tests specified in config-file",
	author  = "abma",
	date    = "Sep. 2010",
	license = "GNU GPL, v2 or later",
	layer   = 0,
	enabled = true,
}
end
if (gadgetHandler:IsSyncedCode()) then
function gadget:GameFrame(n)
	if n==0 then
		Spring.Echo("Going to test...")
		Spring.SendCommands("cheat")
		Spring.SendCommands("setmaxspeed 200")
		Spring.SendCommands("setminspeed 200")
	end
	if n==10 then
		Spring.SendCommands("give all 0")
		Spring.SendCommands("give all 1")
	end
	if n==9000 then
		Spring.Echo("Tests finished after 9000!")
		Spring.SendCommands("quit")
	end
end
end
