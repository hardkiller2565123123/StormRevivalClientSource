package script.gametitle_lu
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.events.IOErrorEvent;
   import flash.events.SecurityErrorEvent;
   import flash.external.*;
   import flash.net.URLLoader;
   import flash.net.URLLoaderDataFormat;
   import flash.net.URLRequest;
   import flash.net.URLRequestHeader;
   import flash.utils.ByteArray;
   import script.gametitle_lu.events.ChannelEvent;
   import script.icon_help.anm_help;
   import script.icon_help.smb_base;
   import script.icon_help.smb_iconbg;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class patch_nut extends MovieClip
   {
      
      private static const URL_RE_MAIN:RegExp = /(https?:\/\/[^\s"'<>]+)/i;
      
      private static const URL_RE_QUOTED:RegExp = /"(https?:\/\/[^"]+)"/i;
      
      private static const VERSION_RE:RegExp = /^\s*(\d+)/;
      
      public var all_icon1:anm_help;
      
      public var all_base:smb_base;
      
      public var all_iconbg:smb_iconbg;
      
      public var txt_title:smb_font;
      
      private var m_title:smb_font;
      
      private var _channel:int = -1;
      
      private var _xfbinPath:String = null;
      
      private var _bridge:ExtendLoader;
      
      private var _mountFrames:int = 0;
      
      private var _cfg:URLLoader;
      
      private var _ver:URLLoader;
      
      private var _inFlight:Boolean = false;
      
      private var _checkedByChannel:Object = {};
      
      private var _checkingGate:Boolean = false;
      
      public function patch_nut()
      {
         super();
         addFrameScript(0,frame1);
         addEventListener(Event.ADDED_TO_STAGE,onAddedToStage,false,0,true);
         addEventListener(Event.REMOVED_FROM_STAGE,onRemovedFromStage,false,0,true);
      }
      
      internal function frame1() : void
      {
         m_title = this.txt_title;
         if(m_title)
         {
            m_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
            m_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
            m_title.SetTextSize(33);
         }
         setUIVisible(false);
      }
      
      private function onAddedToStage(_:Event) : void
      {
         if(stage)
         {
            stage.addEventListener(ChannelEvent.CHANGE,onChannelChange,false,0,true);
         }
         removeEventListener(Event.ADDED_TO_STAGE,onAddedToStage);
      }
      
      private function onRemovedFromStage(_:Event) : void
      {
         if(stage)
         {
            stage.removeEventListener(ChannelEvent.CHANGE,onChannelChange);
         }
         removeEventListener(Event.ENTER_FRAME,pollMount);
         cleanupBridge();
         cleanupConfigLoader();
         cleanupRemoteLoader();
         _inFlight = false;
      }
      
      private function onChannelChange(e:ChannelEvent) : void
      {
         var ch:int = e.value;
         if(_checkedByChannel[ch] === true || _inFlight)
         {
            return;
         }
         _channel = ch;
         _checkedByChannel[ch] = true;
         setUIVisible(false);
         if(_channel < 1000 || _channel >= 3000)
         {
            return;
         }
         if(_channel <= 1999)
         {
            _checkingGate = false;
            _xfbinPath = "../gametitle/evocheck1.xfbin";
         }
         else
         {
            _checkingGate = true;
            _xfbinPath = "../gametitle/evocheck3.xfbin";
         }
         _inFlight = true;
         startMount();
      }
      
      private function startMount() : void
      {
         var bridge:ExtendLoader;
         if(!_xfbinPath)
         {
            finalizeAttempt();
            return;
         }
         bridge = new ExtendLoader();
         _bridge = bridge;
         bridge.visible = false;
         bridge.alpha = 0;
         addChild(bridge);
         try
         {
            bridge.load(new URLRequest(_xfbinPath));
         }
         catch(_:Error)
         {
            cleanupBridge();
            finalizeAttempt();
            return;
         }
         _mountFrames = 0;
         addEventListener(Event.ENTER_FRAME,pollMount,false,0,true);
      }
      
      private function pollMount(_:Event) : void
      {
         var mounted:Boolean;
         ++_mountFrames;
         mounted = false;
         try
         {
            mounted = _bridge && _bridge.IsLoadedXfbin();
         }
         catch(_:Error)
         {
         }
         if(!mounted && _mountFrames < 360)
         {
            return;
         }
         removeEventListener(Event.ENTER_FRAME,pollMount);
         if(!mounted)
         {
            cleanupBridge();
            finalizeAttempt();
            return;
         }
         readConfigBinary();
      }
      
      private function cleanupBridge() : void
      {
         var bridge:ExtendLoader = _bridge;
         if(bridge)
         {
            _bridge = null;
            try
            {
               bridge.unload();
            }
            catch(_:Error)
            {
            }
            if(bridge.parent)
            {
               bridge.parent.removeChild(bridge);
            }
         }
      }
      
      private function readConfigBinary() : void
      {
         var loader:URLLoader = new URLLoader();
         cleanupConfigLoader();
         _cfg = loader;
         loader.dataFormat = URLLoaderDataFormat.BINARY;
         loader.addEventListener(Event.COMPLETE,onConfigComplete,false,0,true);
         loader.addEventListener(IOErrorEvent.IO_ERROR,onConfigError,false,0,true);
         try
         {
            loader.load(new URLRequest(_xfbinPath));
         }
         catch(_:Error)
         {
            cleanupConfigLoader();
            cleanupBridge();
            finalizeAttempt();
         }
      }
      
      private function onConfigError(_:IOErrorEvent) : void
      {
         cleanupConfigLoader();
         cleanupBridge();
         finalizeAttempt();
      }
      
      private function onConfigComplete(_:Event) : void
      {
         if(!_cfg)
         {
            return;
         }
         var bytes:ByteArray = _cfg.data as ByteArray;
         cleanupConfigLoader();
         cleanupBridge();
         var url:String = extractHttpUrlFromBytes(bytes);
         if(!url)
         {
            finalizeAttempt();
            return;
         }
         fetchRemote(url);
      }
      
      private function extractHttpUrlFromBytes(b:ByteArray) : String
      {
         if(!b || b.length == 0)
         {
            return "";
         }
         var len:int = int(b.length);
         var out:Array = new Array(len);
         b.position = 0;
         var i:int = 0;
         while(i < len)
         {
            var x:int = int(b.readUnsignedByte());
            out[i] = x >= 32 && x <= 126 ? String.fromCharCode(x) : " ";
            i++;
         }
         var s:String = out.join("");
         var m:Object = URL_RE_MAIN.exec(s);
         if(m)
         {
            return String(m[1]);
         }
         m = URL_RE_QUOTED.exec(s);
         return m ? String(m[1]) : "";
      }
      
      private function fetchRemote(url:String) : void
      {
         var request:URLRequest;
         var loader:URLLoader = new URLLoader();
         cleanupRemoteLoader();
         _ver = loader;
         loader.dataFormat = URLLoaderDataFormat.TEXT;
         loader.addEventListener(Event.COMPLETE,onRemoteComplete,false,0,true);
         loader.addEventListener(IOErrorEvent.IO_ERROR,onRemoteIoError,false,0,true);
         loader.addEventListener(SecurityErrorEvent.SECURITY_ERROR,onRemoteSecurityError,false,0,true);
         request = new URLRequest(url);
         request.requestHeaders = [new URLRequestHeader("Cache-Control","no-cache"),new URLRequestHeader("Pragma","no-cache")];
         try
         {
            loader.load(request);
         }
         catch(_:Error)
         {
            cleanupRemoteLoader();
            finalizeAttempt();
         }
      }
      
      private function onRemoteIoError(_:IOErrorEvent) : void
      {
         cleanupRemoteLoader();
         finalizeAttempt();
      }
      
      private function onRemoteSecurityError(_:SecurityErrorEvent) : void
      {
         cleanupRemoteLoader();
         finalizeAttempt();
      }
      
      private function onRemoteComplete(_:Event) : void
      {
         if(!_ver)
         {
            return;
         }
         var raw:String = _ver != null ? String(_ver.data) : "";
         cleanupRemoteLoader();
         if(_checkingGate)
         {
            _checkingGate = false;
            var gateStr:String = raw ? raw.replace(/^\s+|\s+$/g,"") : "";
            if(gateStr == "1")
            {
               _xfbinPath = "../gametitle/evocheck2.xfbin";
               _inFlight = true;
               startMount();
            }
            else if(gateStr == "0")
            {
               if(m_title)
               {
                  m_title.SetText(String(ExternalInterface.call("MessageConvert","evo_test_nort")));
                  ExternalInterface.call("RequestPlaySE",39);
               }
               setUIVisible(true);
               finalizeAttempt();
            }
            else
            {
               finalizeAttempt();
            }
            return;
         }
         var remoteMax:Number = extractVersion(raw);
         if(!isFinite(remoteMax))
         {
            finalizeAttempt();
            return;
         }
         if(remoteMax > _channel)
         {
            if(m_title)
            {
               m_title.SetText(String(ExternalInterface.call("MessageConvert","evo_update_nort")));
               ExternalInterface.call("RequestPlaySE",39);
            }
            setUIVisible(true);
         }
         else
         {
            setUIVisible(false);
         }
         finalizeAttempt();
      }
      
      private function extractVersion(text:String) : Number
      {
         if(!text)
         {
            return NaN;
         }
         if(text.length > 0 && text.charCodeAt(0) == 65279)
         {
            text = text.substr(1);
         }
         var m:Object = VERSION_RE.exec(text);
         return m ? int(m[1]) : NaN;
      }
      
      private function setUIVisible(show:Boolean) : void
      {
         if(txt_title)
         {
            txt_title.visible = show;
            txt_title.alpha = show ? 1 : 0;
            if(!show)
            {
               txt_title.SetText("");
            }
         }
         if(all_icon1)
         {
            all_icon1.visible = show;
         }
         if(all_iconbg)
         {
            all_iconbg.visible = show;
         }
         if(all_base)
         {
            all_base.visible = show;
         }
      }
      
      private function finalizeAttempt() : void
      {
         _inFlight = false;
         cleanupConfigLoader();
         cleanupRemoteLoader();
      }
      
      private function cleanupConfigLoader() : void
      {
         var loader:URLLoader = _cfg;
         if(!loader)
         {
            return;
         }
         loader.removeEventListener(Event.COMPLETE,onConfigComplete);
         loader.removeEventListener(IOErrorEvent.IO_ERROR,onConfigError);
         try
         {
            loader.close();
         }
         catch(_:Error)
         {
         }
         _cfg = null;
      }
      
      private function cleanupRemoteLoader() : void
      {
         var loader:URLLoader = _ver;
         if(!loader)
         {
            return;
         }
         loader.removeEventListener(Event.COMPLETE,onRemoteComplete);
         loader.removeEventListener(IOErrorEvent.IO_ERROR,onRemoteIoError);
         loader.removeEventListener(SecurityErrorEvent.SECURITY_ERROR,onRemoteSecurityError);
         try
         {
            loader.close();
         }
         catch(_:Error)
         {
         }
         _ver = null;
      }
   }
}

