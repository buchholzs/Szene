(UMLStudio "5.0" project)
(repository "" 0)
(notation "UML.not")
(genProfile 50 1 "" "" 0 "" "" 951 569 300 233 124 50 80 50 80 60 0 3)
(codeFiles)
(docFiles)
(otherFiles)
(revFiles 1)
(masters (master "37!GK,U;!jD>D!!" 2 3 "StatusObserver" "" "" "" "" "" 1 nil 
                 (("updateStatus" "" "" 3 16 (("status" "string" "" 1)) nil 
                                  "2>!ciGT;!jD>D!!")) nil 10 "") 
         (master "f6!3c<U;!jD>D!!" 2 3 "ControllerTask" "" "" "" "" "" 1 nil 
                 nil nil 10 "") 
         (master "D3! 'sV;!jD>D!!" 3 3 "Hud" "" "" "" "" "" 1 nil 
                 (("setStatusText" "" "" 3 16 (("txt" "string" "" 1)) nil 
                                   "G3!&aoV;!jD>D!!")) nil 10 
                 ":>!&86T;!jD>D!!") 
         (master "J&!,JKX;!jD>D!!" 1 3 "ControllerBase" "" "" "" "" "" 1 nil 
                 (("moveForward" "" "" 3 16 nil nil "M&!SuBX;!jD>D!!") 
                  ("moveFastForward" "" "" 3 16 nil nil "N&!PuAX;!jD>D!!") 
                  ("quit" "" "" 3 16 nil nil "Q&!jS|W;!jD>D!!") 
                  ("turn" "" "" 3 16 nil nil "O&!CB7X;!jD>D!!") 
                  ("turnObject" "" "" 3 16 (("direction" "" "" 1)) nil 
                                ")3!b!&W;!jD>D!!") 
                  ("zoomIn" "" "" 3 16 nil nil "R&!)gzW;!jD>D!!") 
                  ("zoomOut" "" "" 3 16 nil nil "S&! <zW;!jD>D!!") 
                  ("read" "" "Abfrage von Keyboard und Maus" 3 16 nil nil 
                          "L6!q#>U;!jD>D!!") 
                  ("addStatusObserver" "" "" 3 16 
                                       (("obs" "StatusObservable" "" 1)) nil 
                                       "@7!~X)U;!jD>D!!") 
                  ("removeStatusObserver" "" "" 3 16 
                                          (("obs" "StatusObservable" "" 1)) 
                                          nil "A7!^"N#U;!jD>D!!") 
                  ("notifyStatus" "" 
                                  "Benachrichtigt Observer von einem neuen Statustext" 
                                  1 16 (("status" "string" "" 1)) nil 
                                  "6=!h&]T;!jD>D!!")) nil 10 "") 
         (master "H&!avLX;!jD>D!!" 2 3 "Scene" "" "" "" "" "" 1 
                 (("cameras" "" "" "" "" "" 1 16 "e&!NzjW;!jD>D!!") 
                  ("lights" "" "" "" "" "" 1 16 "f&!AJjW;!jD>D!!") 
                  ("objects" "" "" "" "" "" 1 16 "g&!jmiW;!jD>D!!") 
                  ("materials" "" "" "" "" "" 1 16 "h&!'2iW;!jD>D!!") 
                  ("cameras" "" "" "" "" "" 1 16 "i&!0$cW;!jD>D!!")) 
                 (("loadXML" "" "Lädt eine Szenebeschreibung im XML-Format" 3 
                             16 (("fileName" "string" "" 1)) nil 
                             "]'!hW]W;!jD>D!!") 
                  ("getCurrCamera" "pl_Cam" 
                                   "Liefert die z.Zt. selektierte Kamera" 3 18 
                                   nil nil "/4!st<V;!jD>D!!") 
                  ("findCamera" "pl_Cam*" 
                                "Liefert eine Kamera aus der Szenebeschreibung" 
                                3 16 (("name" "string" "" 1)) nil 
                                "P4!E\7V;!jD>D!!") 
                  ("findObject" "pl_Object*" 
                                "Liefert ein Objekt aus der Szenebeschreibung" 
                                3 16 (("name" "string" "" 1)) nil 
                                "Q4!=V$V;!jD>D!!") 
                  ("findLight" "pl_Light" 
                               "Liefert ein Licht aus der Szenebeschreibung" 3 
                               16 (("name" "string" "" 1)) nil 
                               "F5!4reU;!jD>D!!") 
                  ("TaskMain" "" "" 3 16 nil nil "!6!v?LU;!jD>D!!")) nil 10 "") 
         (master ":&!lhtX;!jD>D!!" 1 3 "Szene" "" "" "" "" "" 1 nil nil nil -1 
                 "") 
         (master ",&!]`8Y;!jD>D!!" 1 3 "Kamera wählen" "" "" "" "" "" 0 nil 
                 nil nil 13 "") 
         (master "+&!/y9Y;!jD>D!!" 1 3 "XML laden" "" "" "" "" "" 0 nil nil 
                 nil 13 "") 
         (master "*&!dI;Y;!jD>D!!" 1 3 "Abfragen stellen" "" "" "" "" "" 0 nil 
                 nil nil 13 "") 
         (master "&&!S\=Y;!jD>D!!" 1 3 "Rendern" "" "" "" "" "" 0 nil nil nil 
                 13 "") 
         (master "$&!7c@Y;!jD>D!!" 2 3 "Betrachter" "" "" "" "" "" 0 nil nil 
                 nil 14 "") 
         (master "g&!f7Ga;!|acP%!" 1 4 "Task" "" 
                 "D:\Projekte\TASKS\INC\TASK.H" 
                 "------------------------------------------------------------
CLASS TASK **********

class Task implements the basic schedulable entity...
------------------------------------------------------------" "" "" 0 
                 (("stkval" "uchar" "" "" "" "value to fill stack with" 1 3 
                            "i&!e7Ga;!|acP%!") 
                  ("tskname" "char*" "" "" "" "" 1 16 "j&!e7Ga;!|acP%!") 
                  ("tskEnv" "jmp_buf" "" "" "" 
                            "environment for context switching" 1 0 
                            "k&!e7Ga;!|acP%!") 
                  ("stklen" "int" "" "" "" "length of task's stack" 1 0 
                            "l&!e7Ga;!|acP%!") 
                  ("stack" "uchar*" "" "" "" "this task's stack space" 1 0 
                           "m&!e7Ga;!|acP%!") 
                  ("wakeUp" "clock_t" "" "" "" "when to wake up if asleep" 1 
                            0 "n&!e7Ga;!|acP%!") 
                  ("tskpri" "int" "" "" "" "" 1 16 "o&!e7Ga;!|acP%!")) 
                 (("isInited" "int" "task priority
get state of flags" 1 0 nil nil "p&!e7Ga;!|acP%!") 
                  ("isReady" "int" "" 1 0 nil nil "q&!e7Ga;!|acP%!") 
                  ("isTimed" "int" "" 1 0 nil nil "r&!e7Ga;!|acP%!") 
                  ("isZombie" "int" "" 1 0 nil nil "s&!e7Ga;!|acP%!") 
                  ("shouldDelete" "int" "" 1 0 nil nil "t&!e7Ga;!|acP%!") 
                  ("timeOut" "int" 
                             "clear fTimed flag and return previous value" 1 
                             0 nil nil "u&!e7Ga;!|acP%!") 
                  ("init" "void" "set up stack and begin execution" 1 0 nil 
                          nil "v&!e7Ga;!|acP%!") 
                  ("resume" "void" "return to place of last suspend()" 1 0 
                            (("code" "int" "1" 0)) nil "w&!e7Ga;!|acP%!") 
                  ("maybeWake" "int" "possibly wake up a timed task" 1 0 nil 
                               nil "x&!e7Ga;!|acP%!") 
                  ("block" "int" 
                           "if blocked, task will wait until another unblocks it" 
                           1 0 (("msec" "clock_t" "WaitForever" 0)) nil 
                           "y&!e7Ga;!|acP%!") 
                  ("unblock" "void" "make task ready to execute again" 1 0 
                             nil nil "z&!e7Ga;!|acP%!") 
                  ("stackok" "int" "check if stack bashed" 1 0 nil nil 
                             "{&!e7Ga;!|acP%!") 
                  ("Task" "" "constructor, destructor" 3 0 
                          (("tname" "char*" "" 0) ("stk" "int" "StackMin" 0)) 
                          nil "|&!e7Ga;!|acP%!") 
                  ("~Task" "" "" 3 8 nil nil "}&!e7Ga;!|acP%!") 
                  ("name" "char*" "get name of task" 3 0 nil nil 
                          "~&!e7Ga;!|acP%!") 
                  ("setDelete" "void" "set the delete flag" 3 0 nil nil 
                               "!'!e7Ga;!|acP%!") 
                  ("suicide" "void" "shut down one task" 3 8 nil nil 
                             "^"'!e7Ga;!|acP%!") 
                  ("TaskMain" "void" "the main routine for each task" 3 24 
                              nil nil "#'!e7Ga;!|acP%!") 
                  ("suspend" "int" "voluntarily give up control" 3 16 nil nil 
                             "$'!e7Ga;!|acP%!") 
                  ("sleep" "void" "wait a specified amount of time" 3 16 
                           (("msec" "clock_t" "" 0)) nil "%'!e7Ga;!|acP%!") 
                  ("priority" "int" "get, set priority" 3 0 nil nil 
                              "&'!e7Ga;!|acP%!") 
                  ("priority" "int" "" 3 16 (("newpri" "int" "" 0)) nil 
                              "''!e7Ga;!|acP%!") 
                  ("operator<" "int" "compare tasks for priority" 3 0 
                               (("t" "Qable&" "" 0)) nil "('!e7Ga;!|acP%!")) 
                 nil 10 ""))
(customModel "#&!>@DY;!jD>D!!" 0 3 "Aufgaben der Szene" "" "" 1 "" "" 1.000000 
             1.000000 (0 0 827 1168) (0 0 827 1168) 
             (placeGroup (group ((place "*&!dI;Y;!jD>D!!" (1) "" 13 
                                        "'&!S\=Y;!jD>D!!" (198 66 291 110) 
                                        (193 61 296 115) (205 72 284 104) 1 0 
                                        (nil 1 -12 32 18 12 11 18) 
                                        "9&!lhtX;!jD>D!!") 
                                 (place "+&!/y9Y;!jD>D!!" (1) "" 13 
                                        "(&![==Y;!jD>D!!" (195 126 269 162) 
                                        (190 121 274 167) (201 131 263 157) 1 
                                        0 (nil 1 -12 32 18 12 11 18) 
                                        "9&!lhtX;!jD>D!!") 
                                 (place "&&!S\=Y;!jD>D!!" (1) "" 13 
                                        ")&!=~<Y;!jD>D!!" (259 162 333 198) 
                                        (254 157 338 203) (265 167 327 193) 1 
                                        0 (nil 1 -12 32 18 12 11 18) 
                                        "9&!lhtX;!jD>D!!") 
                                 (place ",&!]`8Y;!jD>D!!" (1) "" 13 
                                        "-&!]`8Y;!jD>D!!" (199 202 297 246) 
                                        (194 197 302 251) (207 208 290 240) 1 
                                        0 (nil 1 -12 32 18 12 11 18) 
                                        "9&!lhtX;!jD>D!!")) 33 
                                "9&!lhtX;!jD>D!!" (191 43 337 250) 
                                (186 38 342 255) (194 46 334 62) 4 1 
                                (nil 1 -12 32 18 12 18 18) "8&!lhtX;!jD>D!!") 
                         place ":&!lhtX;!jD>D!!" (73) "" 34 "8&!lhtX;!jD>D!!" 
                         (191 43 337 250) (186 38 342 255) (194 46 334 62) 1 1 
                         (nil 1 -12 32 18 12 18 18) "") 
             (place "$&!7c@Y;!jD>D!!" (1) "" 14 "%&!7c@Y;!jD>D!!" 
                    (13 119 83 169) (8 114 88 174) (13 153 83 169) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (link "%&!7c@Y;!jD>D!!" "(&![==Y;!jD>D!!" (82 144 194 144) 3 "" 
                   "" "%%" "%%" "" "" 1 0 (128 136 148 152) (90 140 90 140) 
                   (186 140 186 140) 6 6 "<&!6noX;!jD>D!!" (128 136 148 152) 
                   (77 124 199 164) (128 136 148 152) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (link "%&!7c@Y;!jD>D!!" "-&!]`8Y;!jD>D!!" (82 157 198 204) 3 "" 
                   "" "%%" "%%" "" "" 1 0 (130 172 150 188) (90 153 90 153) 
                   (190 208 190 208) 6 6 ">&!6*nX;!jD>D!!" (82 157 198 204) 
                   (76 142 204 219) (130 172 150 188) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (link "%&!7c@Y;!jD>D!!" "'&!S\=Y;!jD>D!!" (82 133 197 101) 3 "" 
                   "" "%%" "%%" "" "" 1 0 (129 109 149 125) (90 137 90 137) 
                   (189 97 189 97) 6 6 "@&!2ViX;!jD>D!!" (82 101 197 133) 
                   (76 85 203 149) (129 109 149 125) 2 0 
                   (nil 1 -12 32 18 12 18 18) ""))
(customModel "A&!:WRX;!jD>D!!" 11 3 "Szene Klassen" "" "" 5 "" "" 1.000000 
             1.000000 (0 0 827 1168) (0 0 827 1168) 
             (place "H&!avLX;!jD>D!!" (1) "" 10 "I&!avLX;!jD>D!!" 
                    (135 218 233 406) (130 213 238 411) (136 221 232 403) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (place "J&!,JKX;!jD>D!!" (1) "" 10 "K&!,JKX;!jD>D!!" 
                    (338 17 478 207) (333 12 483 212) (340 20 476 204) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (place "g&!f7Ga;!|acP%!" (1) "" 10 "h&!e7Ga;!|acP%!" 
                    (171 16 243 134) (166 11 248 139) (172 18 242 132) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (link "I&!avLX;!jD>D!!" "h&!e7Ga;!|acP%!" (184 218 184 133) 3 "" 
                   "" "%%" "%%" "" "" 3 0 (175 168 193 182) (188 210 188 210) 
                   (176 141 176 141) 0 0 "}2!0>5W;!jD>D!!" (174 167 194 183) 
                   (169 128 199 223) (174 167 194 183) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (place "D3! 'sV;!jD>D!!" (1) "" 10 "E3! 'sV;!jD>D!!" 
                    (510 273 602 319) (505 268 607 324) (511 274 601 318) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (place "f6!3c<U;!jD>D!!" (1) "" 10 "g6!3c<U;!jD>D!!" 
                    (286 255 378 281) (281 250 383 286) (287 256 377 280) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (link "g6!3c<U;!jD>D!!" "K&!,JKX;!jD>D!!" (360 255 360 205) 3 "" 
                   "" "%%" "%%" "" "" 3 0 (351 223 369 237) (356 247 356 247) 
                   (356 213 356 213) 0 0 "i6!Li4U;!jD>D!!" (350 222 370 238) 
                   (345 200 375 260) (350 222 370 238) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (link "g6!3c<U;!jD>D!!" "h&!e7Ga;!|acP%!" 
                   (308 255 308 188 228 188 228 133) 3 "" "" "%%" "%%" "" "" 3 
                   1 (259 181 277 195) (304 247 304 247) (224 141 224 141) 0 0 
                   "j6!iT3U;!jD>D!!" (228 133 308 255) (213 128 323 260) 
                   (258 180 278 196) 2 0 (nil 1 -12 32 18 12 18 18) "") 
             (place "37!GK,U;!jD>D!!" (1) "" 10 "47!GK,U;!jD>D!!" 
                    (505 166 615 210) (500 161 620 215) (506 167 614 209) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (link "K&!,JKX;!jD>D!!" "47!GK,U;!jD>D!!" 
                   (477 120 544 120 544 166) 3 "" "" "%%" "%%" "" "" 2 1 
                   (534 135 554 151) (485 116 485 116) (540 158 540 158) 8 8 
                   "'=!\2dT;!jD>D!!" (477 120 554 166) (472 100 559 171) 
                   (534 135 554 151) 2 0 (nil 1 -12 32 18 12 18 18) "") 
             (tag "K&!,JKX;!jD>D!!" (477 89) 
                  "notifyStatus() {
for i in statusObservers {
i.updateStatus()
}
}" 25 "7>!BSET;!jD>D!!" (541 15 683 99) (472 10 688 104) (544 18 680 96) 3 0 
                  (nil 1 -12 0 0 4 15 0) ""))
(customModel ":>!&86T;!jD>D!!" 11 3 "Hud" "" "" 21 "D3! 'sV;!jD>D!!" 
             "A&!:WRX;!jD>D!!" 1.000000 1.000000 (0 0 827 1168) (0 0 827 1168) 
             (place "37!GK,U;!jD>D!!" (1) "" 10 "@>!2-/T;!jD>D!!" 
                    (163 33 261 79) (158 28 266 84) (164 34 260 78) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (place "D3! 'sV;!jD>D!!" (0) "" 10 "i*!9giY;!*p4<!!" 
                    (174 163 242 189) (169 158 247 194) (175 164 241 188) 1 0 
                    (nil 1 -12 32 18 12 18 18) "") 
             (link "i*!9giY;!*p4<!!" "@>!2-/T;!jD>D!!" (212 163 212 79) 3 "" 
                   "" "%%" "%%" "" "" 3 0 (202 113 222 129) (208 155 208 155) 
                   (208 87 208 87) 101 101 "}*!``YY;!*p4<!!" 
                   (202 113 222 129) (197 74 227 168) (202 113 222 129) 2 0 
                   (nil 1 -12 32 18 12 18 18) ""))
(customModel "S'!Wc.Z;!*p4<!!" 13 3 "Untitled 1" "" "" 16 "" "" 1.000000 
             1.000000 (0 0 827 1168) (0 0 827 1168) 
             (scenPlace (88 481) place "$&!7c@Y;!jD>D!!" (0) "" 14 
                        "]*!?2*Z;!*p4<!!" (53 67 123 117) (48 62 128 486) 
                        (53 101 123 117) 1 4 (nil 1 -12 32 18 12 18 18) "") 
             (scenPlace (212 473) place "H&!avLX;!jD>D!!" (0) "" 10 
                        " *!7D&Z;!*p4<!!" (188 75 236 101) (183 70 241 478) 
                        (189 76 235 100) 1 4 (nil 1 -12 32 18 12 18 18) "") 
             (link "]*!?2*Z;!*p4<!!" " *!7D&Z;!*p4<!!" (88 152 212 152) 3 
                   "loadXML ()" "" "%%" "%%" "" "" 8 0 (118 143 182 161) 
                   (96 133 118 148) (182 133 204 148) 9 9 "`*!` !Z;!*p4<!!" 
                   (118 143 182 161) (83 128 217 172) (118 143 182 161) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (scenPlace (340 473) place "f6!3c<U;!jD>D!!" (0) "" 10 
                        "a*!x&zY;!*p4<!!" (289 75 391 101) (284 70 396 478) 
                        (290 76 390 100) 1 4 (nil 1 -12 32 18 12 18 18) "") 
             (link " *!7D&Z;!*p4<!!" " *!7D&Z;!*p4<!!" 
                   (212 176 260 176 260 200 212 200) 3 "TaskMain ()" "" "%%" 
                   "%%" "" "" 8 1 (224 179 296 197) (220 157 242 172) 
                   (220 181 242 196) 9 9 "f*!fRrY;!*p4<!!" (212 176 296 200) 
                   (207 152 301 220) (224 179 296 197) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (link "a*!x&zY;!*p4<!!" " *!7D&Z;!*p4<!!" (340 252 212 252) 3 
                   "getCurrCamera ()" "" "%%" "%%" "" "" 8 0 (222 243 330 261) 
                   (310 233 332 248) (220 233 242 248) 9 9 "g*!oEoY;!*p4<!!" 
                   (222 243 330 261) (207 228 345 272) (222 243 330 261) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (scenPlace (488 469) place "D3! 'sV;!jD>D!!" (0) "" 10 
                        "h*!3xlY;!*p4<!!" (453 75 523 101) (448 70 528 474) 
                        (454 76 522 100) 1 4 (nil 1 -12 32 18 12 18 18) "") 
             (link "a*!x&zY;!*p4<!!" "a*!x&zY;!*p4<!!" 
                   (340 268 396 268 396 292 340 292) 3 "turn ()" "" "%%" "%%" 
                   "" "" 8 1 (378 271 414 289) (348 249 370 264) 
                   (348 273 370 288) 9 9 "S+!i(EY;!*p4<!!" (340 268 414 292) 
                   (335 244 419 312) (378 271 414 289) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (link "a*!x&zY;!*p4<!!" "a*!x&zY;!*p4<!!" 
                   (340 324 396 324 396 348 340 348) 3 "moveForward ()" "" 
                   "%%" "%%" "" "" 8 1 (348 327 444 345) (348 305 370 320) 
                   (348 329 370 344) 9 9 "T+!EuBY;!*p4<!!" (340 324 444 348) 
                   (335 300 449 368) (348 327 444 345) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (link "]*!?2*Z;!*p4<!!" "a*!x&zY;!*p4<!!" (88 232 340 232) 3 
                   "read ()" "" "%%" "%%" "" "" 8 0 (194 223 234 241) 
                   (96 213 118 228) (310 213 332 228) 7 7 "V+!^"E;Y;!*p4<!!" 
                   (194 223 234 241) (83 208 345 252) (194 223 234 241) 2 0 
                   (nil 1 -12 32 18 12 18 18) "") 
             (text "2. Eingabe verarbeiten" 1 28 "X+!tk1Y;!*p4<!!" 
                   (360 228 504 256) (355 223 509 261) (360 228 504 256) 4 0 
                   (nil 1 -12 0 0 4 15 0) "") 
             (text "1. Szene einlesen" 1 28 "Y+!M..Y;!*p4<!!" 
                   (224 124 336 152) (219 119 341 157) (224 124 336 152) 4 0 
                   (nil 1 -12 0 0 4 15 0) ""))
