#pragma once
/* ======================================================================= */
// trio (cool hack name) credits										   //
/* ======================================================================= */
// Project started: Dec 25, 2018									       //
/* ======================================================================= */
// Credits
//
// ensidiya
// wando    - created antario & color picker
// shiro    - redid entire esp & helped with many things in this hack
// hopdog   - cause some stuff shiro gave me was from shiro and hopdogs hack
// bolbi    - helped with multibox & fixing stuff
// floody   - (i pasted his backtrack, hitmarker & texture rendering thing)
// quantiom - helped with hooks & stuff
// czapek   - gave me copy & paste hex function for color picker (ctrl c + ctrl v)
// gabe     - i stole some of his stuff
// cYb2     - i stole some of his hooks
// normie   - helped with stuff
//
/* ======================================================================= */
//
// im releasing this source because alot of stuff is aids and pasted.
//
/* ======================================================================= */
//
// stuff to fix:
//
// alpha for menu - aids but works lmao
//
// nightmode - spams the console, you gotta click the button again to remove
// the spam.
// 
// offscreen esp - never fixed it, it works sometimes, but it usually has a
// random arrow just chilling
//
// listbox - never fixed / finished it
//
// blend while scoped - sometimes flips world up (cant rly explain)
//
// fullbright - when you turn off the world flashes black
//
// bullet tracers - they don't always work and sometimes will not show up
//
// footstep esp - has random cuts & is done in event manager (use getactivesound)
//
// configs - they never worked, tried once, gave up
//
// disable post processing - removed cause broke sv_cheats
//
// bomb timer - works, just will keep counting no matter what
//
// projectiles - if you throw a molotov and wait till the round ends and the
// molotov didnt expire, the circle will stay for the rest of the game
//
// remove scope - works, but you sometimes get a crosshair flash when loading in
//
// auto strafer - works, just is aids code
//
// skeleton esp - in code, just doesnt work (messes up and flips up chams)
//
// color pickers - copy & paste doesnt update the color picker (inside the picker)
//
// backtrack chams - in code, just spazzes out and does sketch stuff
//
// every outlined text - the code is aids, i made the text render 10 times.
//
// player ammo - doesnt have reload animation (just visual)
//
// grenade pred - absolute trash, works just very hardcoded
//
// force crosshair - works, just doesn't remove when scoped, or when you turn off
/* ======================================================================= */
