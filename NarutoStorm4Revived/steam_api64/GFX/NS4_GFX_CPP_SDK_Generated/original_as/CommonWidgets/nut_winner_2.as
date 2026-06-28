package script.result_main
{
   import ELoader.ExtendLoader;
   import KeyHelp.KeyHelpCode;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.icon_player_m_txt.nut_icon_player_m;
   import script.xcmn_tex00.nut_tex00;
   import script.xct_fad2.smb_xct_fad2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol150")]
   public class nut_winner extends MovieClip
   {
      
      internal static const PLAYER_1P:int = 0;
      
      internal static const PLAYER_2P:int = 1;
      
      internal static const PLAYER_3P:int = 2;
      
      internal static const PLAYER_4P:int = 3;
      
      internal static const PLAYER_5P:int = 4;
      
      internal static const PLAYER_6P:int = 5;
      
      internal static const PLAYER_7P:int = 6;
      
      internal static const PLAYER_8P:int = 7;
      
      internal static const PLAYER_COM:int = 8;
      
      public var dmy_name:nut_tex00;
      
      public var dmy_title:nut_tex00;
      
      public var mc_fad_b:smb_xct_fad2;
      
      public var mc_fad_t:smb_xct_fad2;
      
      public var mc_foc:MovieClip;
      
      public var mc_icon:nut_icon_player_m;
      
      public var NoticeEndOutAnm:Function;
      
      private var m_attachObj:MovieClip;
      
      private var m_loaderObj:ExtendLoader;
      
      private var m_rsltloaderObj:Object;
      
      private var m_url:URLRequest;
      
      private var m_charCode:String;
      
      private var m_keyHelp:KeyHelpCode;
      
      private var m_isEndCharaVoice:Boolean;
      
      private var m_isChangedKeyHelp:Boolean;
      
      private var m_isCheckLoad:Boolean;
      
      public function nut_winner()
      {
         super();
         addFrameScript(84,this.frame85,96,this.frame97);
         this.m_attachObj = null;
         this.m_loaderObj = null;
         this.m_url = null;
         this.m_charCode = "";
         this.m_isEndCharaVoice = false;
         this.m_isChangedKeyHelp = false;
         this.m_isCheckLoad = false;
         this.m_rsltloaderObj = new Object();
         this.m_rsltloaderObj.loader = new ExtendLoader();
         this.m_rsltloaderObj.bCheck = false;
         this.m_rsltloaderObj.loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_LEFT);
         this.m_keyHelp = new KeyHelpCode();
         if(this.m_keyHelp != null)
         {
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_SKIP);
            this.m_keyHelp.PushKeyHelp();
         }
         addEventListener(Event.ENTER_FRAME,this.OnFrameUpdate);
      }
      
      public function OnFrameUpdate() : *
      {
         if(this.m_isCheckLoad)
         {
            if(this.m_loaderObj.IsLoadedAll() && Boolean(this.m_rsltloaderObj.loader.IsLoadedAll()))
            {
               this.onLoadComplete();
            }
         }
         if(!this.m_isChangedKeyHelp && this.m_isEndCharaVoice && this.m_keyHelp != null)
         {
            this.m_keyHelp.PopKeyHelp();
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_NEXT);
            this.m_keyHelp.PushKeyHelp();
            this.m_isChangedKeyHelp = true;
         }
         if(currentLabel == "end")
         {
            this.NoticeEndOutAnm();
         }
      }
      
      public function SetPlayerNo(param1:int) : *
      {
         if(this.mc_icon == null)
         {
            return;
         }
         switch(param1)
         {
            case PLAYER_1P:
               this.mc_icon.gotoAndStop("1p");
               break;
            case PLAYER_2P:
               this.mc_icon.gotoAndStop("2p");
               break;
            case PLAYER_3P:
               this.mc_icon.gotoAndStop("3p");
               break;
            case PLAYER_4P:
               this.mc_icon.gotoAndStop("4p");
               break;
            case PLAYER_5P:
               this.mc_icon.gotoAndStop("5p");
               break;
            case PLAYER_6P:
               this.mc_icon.gotoAndStop("6p");
               break;
            case PLAYER_7P:
               this.mc_icon.gotoAndStop("7p");
               break;
            case PLAYER_8P:
               this.mc_icon.gotoAndStop("8p");
               break;
            case PLAYER_COM:
               this.mc_icon.gotoAndStop("com");
         }
      }
      
      public function SetCharaCode(param1:String) : void
      {
         var _loc2_:URLRequest = null;
         var _loc3_:String = null;
         trace("SetCharaCode");
         this.RequestUnload();
         if(this.m_rsltloaderObj.bCheck == false)
         {
            _loc3_ = "LANG/rslt_win.xfbin";
            _loc2_ = null;
            _loc2_ = new URLRequest(_loc3_);
            this.m_rsltloaderObj.loader.load(_loc2_);
            this.m_rsltloaderObj.bCheck = true;
         }
         if(this.m_loaderObj == null && this.m_url == null)
         {
            this.m_charCode = "nl_" + param1;
            this.m_loaderObj = new ExtendLoader();
            this.m_loaderObj.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            this.m_url = new URLRequest("../name_l/LANG/" + this.m_charCode + ".xfbin");
            this.m_loaderObj.load(this.m_url);
            this.m_isCheckLoad = true;
         }
      }
      
      public function RequestSkip() : void
      {
         gotoAndStop("loop");
      }
      
      public function RequestClose() : void
      {
         gotoAndPlay("out");
         if(this.m_keyHelp != null)
         {
            this.m_keyHelp.PopKeyHelp();
         }
      }
      
      internal function onLoadComplete() : void
      {
         trace("Load complete");
         trace("");
         this.dmy_title.visible = true;
         this.dmy_title.addChild(this.m_rsltloaderObj.loader);
         this.m_rsltloaderObj.loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_LEFT);
         this.dmy_name.visible = true;
         this.dmy_name.addChild(this.m_loaderObj);
         this.m_loaderObj.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         this.m_isCheckLoad = false;
      }
      
      public function RequestUnload() : void
      {
         if(this.m_loaderObj != null)
         {
            this.dmy_name.removeChild(this.m_loaderObj);
            this.m_loaderObj.unload();
            this.m_loaderObj = null;
            this.m_url = null;
         }
      }
      
      public function SetEndCharaVoice(param1:Boolean) : void
      {
         this.m_isEndCharaVoice = param1;
      }
      
      internal function frame85() : *
      {
         stop();
      }
      
      internal function frame97() : *
      {
         stop();
      }
   }
}

