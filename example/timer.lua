--[[
  
  Copyright (C) 2014 Masatoshi Teruya

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

  example/timer.lua
  lua-coevent

  Created by Masatoshi Teruya on 14/05/13.
  
--]]

local event = require('coevent');

local function callback( ctx, watcher, hup )
    ctx.count = ctx.count + 1;
    print( 'callback', ctx.count );
    if ctx.count > 2 then
        watcher:unwatch();
    end
end

-- create loop
local loop = event.loop();
-- create timer watcher
local watcher = event.timer( loop, 2 );
local oneshot = false;

watcher:watch( oneshot, callback, { count = 0 } );
print( 'calling callback function every 2 sec.' );
print( 'done', loop:run() );

