package script.result_main
{
   import ELoader.ExtendLoader;
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import flash.net.URLRequest;
   import script.icon_up.nut_up1;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol131")]
   public class nut_rslt_b extends MovieClip
   {
      
      internal static const STEP_NONE:Number = 0;
      
      internal static const STEP_IN:Number = 1;
      
      internal static const STEP_IN_END:Number = 2;
      
      internal static const STEP_IDLE:Number = 3;
      
      internal static const STEP_OUT_ANIME:Number = 4;
      
      internal static const STEP_OUT_ANIME_END:Number = 5;
      
      internal static const STEP_CLOSE:Number = 6;
      
      internal static const STEP_CLOSE_END:Number = 7;
      
      internal static const STEP_END:Number = 8;
      
      internal static const STEP_NUM:Number = 9;
      
      internal static const STEP_CLOSE_WAIT:Number = 10;
      
      public var dmy_title_b:nut_tex00;
      
      public var dmy_title_b2:nut_tex00;
      
      public var mc_boss_sub:MovieClip;
      
      public var mc_chap0:MovieClip;
      
      public var mc_chap1:MovieClip;
      
      public var mc_chap2:MovieClip;
      
      public var mc_chap3:MovieClip;
      
      public var mc_chap4:MovieClip;
      
      public var mc_title_all:MovieClip;
      
      public var mc_up:nut_up1;
      
      public var GetEpsodeNamePath:Function;
      
      public var GetEpsodeName:Function;
      
      public var GetEpsodeData:Function;
      
      public var GetEpsodeDataNum:Function;
      
      public var GetTotalRank:Function;
      
      public var GetTotalMoney:Function;
      
      public var IsRankUp:Function;
      
      public var SetDecide:Function;
      
      public var SetClosed:Function;
      
      public var SetBonusWait:Function;
      
      public var SetOpen:Function;
      
      public var SetSelectResult:Function;
      
      private var m_step:int;
      
      private var m_resultData:Array;
      
      private var m_resultDataNum:int;
      
      private var m_epsodeTitle:Object;
      
      private var m_allAttach:Boolean;
      
      private var m_isRankUp:Boolean;
      
      private var m_inputPad:InputPadKeyCode = null;
      
      private var m_keyHelp:KeyHelpCode = null;
      
      private var m_isDrawItemList:Boolean;
      
      private var m_isNoPlayChapter:Boolean;
      
      private var m_isBgEnd:Boolean;
      
      private var m_isBrtEpisode:Boolean = false;
      
      public function nut_rslt_b()
      {
         super();
         addFrameScript(76,this.frame77);
         this.m_step = STEP_NONE;
         this.m_resultDataNum = 0;
         this.m_epsodeTitle = new Object();
         this.m_epsodeTitle.exloader = new ExtendLoader();
         this.m_epsodeTitle.isAttach = false;
         this.m_epsodeTitle.epsodeName = null;
         this.m_allAttach = false;
         this.m_isRankUp = false;
         this.m_isDrawItemList = false;
         this.m_isNoPlayChapter = false;
         this.m_isBgEnd = false;
      }
      
      public function Initialize(param1:Boolean) : void
      {
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         if(this.m_inputPad == null)
         {
            this.m_inputPad = new InputPadKeyCode();
         }
         if(this.m_keyHelp == null)
         {
            this.m_keyHelp = new KeyHelpCode();
         }
         this.m_isDrawItemList = param1;
         this.m_resultDataNum = this.GetEpsodeDataNum();
         this.m_resultData = new Array(this.m_resultDataNum);
         var _loc2_:int = 0;
         while(_loc2_ < this.m_resultDataNum)
         {
            this.m_resultData[_loc2_] = new Object();
            this.m_resultData[_loc2_].iconPlLoader = new ExtendLoader();
            this.m_resultData[_loc2_].iconEnLoader = new ExtendLoader();
            this.m_resultData[_loc2_].isAttach = false;
            this.m_resultData[_loc2_].battleType = 0;
            this.m_resultData[_loc2_].playerIcon = null;
            this.m_resultData[_loc2_].enemyIcon = null;
            this.m_resultData[_loc2_].chpterName = null;
            this.m_resultData[_loc2_].rate = 0;
            this.m_resultData[_loc2_].isRankUp = false;
            this.m_resultData[_loc2_].isNoPlay = false;
            _loc2_++;
         }
         this.GetEpsodeData(this.m_resultData);
         trace("m_resultDataNum :" + this.m_resultDataNum);
         var _loc3_:int = 0;
         while(_loc3_ < this.m_resultDataNum)
         {
            if(this.m_resultData[_loc3_].isNoPlay == true)
            {
               this.m_isNoPlayChapter = true;
            }
            _loc3_++;
         }
         this.m_isRankUp = this.IsRankUp();
         if(this.m_isRankUp == false)
         {
            this.mc_up.visible = false;
         }
         this.RequestLoad();
         this.DisablePad();
         this.stop();
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc2_:uint = 0;
         switch(this.m_step)
         {
            case STEP_NONE:
               trace("STEP_NONE");
               break;
            case STEP_IN:
               if(this.currentFrameLabel == "create")
               {
                  this.gotoAndPlay("create");
                  this.mc_boss_sub.txt_boss_sub.SetText(this.m_epsodeTitle.epsodeName);
                  this.mc_title_all.txt_msg.SetText(ExternalInterface.call("MessageConvert","battleresult_072"));
                  this.m_step = STEP_IN_END;
                  trace("STEP_IN");
               }
               if(this.currentFrameLabel == "rate_in")
               {
               }
               break;
            case STEP_IN_END:
               if(this.currentFrameLabel == "loop")
               {
                  this.SetOpen(true);
                  this.SetUpKeyHelp();
                  this.m_step = STEP_IDLE;
                  trace("STEP_IN_END BOSS1");
               }
               break;
            case STEP_IDLE:
               _loc2_ = this.m_inputPad.GetPadPress();
               if(this.m_inputPad.GetKeyInputBtn_Ok() & _loc2_)
               {
                  this.m_keyHelp.PopKeyHelp();
                  this.m_step = STEP_CLOSE_WAIT;
                  this.SetBonusWait(true);
                  ExternalInterface.call("RequestPlaySE_Fix");
               }
               else if(this.m_inputPad.GetKeyInputBtn_R_Left() & _loc2_)
               {
                  this.m_keyHelp.PopKeyHelp();
                  this.DisablePad();
                  this.SetDecide(true);
                  this.SetSelectResult(0);
                  ExternalInterface.call("RequestPlaySE_Fix");
               }
               else if(this.m_inputPad.GetKeyInputBtn_Start() & _loc2_)
               {
                  if(this.m_isDrawItemList == true)
                  {
                     this.m_keyHelp.PopKeyHelp();
                     this.DisablePad();
                     this.SetDecide(true);
                     this.SetSelectResult(1);
                     ExternalInterface.call("RequestPlaySE_Fix");
                  }
               }
               break;
            case STEP_CLOSE_WAIT:
               break;
            case STEP_CLOSE:
               this.m_step = STEP_CLOSE_END;
               trace("STEP_CLOSE");
               break;
            case STEP_CLOSE_END:
               if(this.currentFrame == this.totalFrames)
               {
                  this.stop();
                  this.m_step = STEP_END;
                  trace("STEP_CLOSE_END");
                  this.SetClosed(true);
               }
               break;
            case STEP_END:
         }
      }
      
      public function RequestCloseBossResult() : void
      {
         trace("RequestCloseBossResult");
         this.m_step = STEP_CLOSE;
         this.gotoAndPlay("out");
      }
      
      public function RequestLoad() : void
      {
         var _loc1_:URLRequest = null;
         trace("RequestLoad");
         var _loc2_:String = this.GetEpsodeNamePath();
         this.m_isBrtEpisode = _loc2_.indexOf("brt") >= 0;
         trace("Path : " + _loc2_);
         _loc1_ = null;
         _loc1_ = new URLRequest(_loc2_);
         this.m_epsodeTitle.exloader.load(_loc1_);
         this.m_epsodeTitle.epsodeName = this.GetEpsodeName();
         var _loc3_:int = 0;
         while(_loc3_ < this.m_resultDataNum)
         {
            _loc1_ = null;
            _loc1_ = new URLRequest("../charicon_vs/vs_" + this.m_resultData[_loc3_].playerIcon + ".xfbin");
            this.m_resultData[_loc3_].iconPlLoader.load(_loc1_);
            _loc1_ = null;
            _loc1_ = new URLRequest("../charicon_vs/vs_" + this.m_resultData[_loc3_].enemyIcon + ".xfbin");
            this.m_resultData[_loc3_].iconEnLoader.load(_loc1_);
            _loc3_++;
         }
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameLoadCheck);
      }
      
      public function onEnterFrameLoadCheck(param1:*) : void
      {
         var _loc2_:Boolean = false;
         var _loc3_:int = 0;
         var _loc4_:* = undefined;
         var _loc5_:* = undefined;
         var _loc6_:* = undefined;
         var _loc7_:* = undefined;
         var _loc8_:* = undefined;
         var _loc9_:String = null;
         if(this.currentFrame >= 17)
         {
            _loc2_ = false;
            if(this.m_epsodeTitle.exloader.IsLoadedXfbin())
            {
               if(this.m_epsodeTitle.isAttach == false)
               {
                  if(this.m_isBrtEpisode == true)
                  {
                     this.dmy_title_b2.addChild(this.m_epsodeTitle.exloader);
                  }
                  else
                  {
                     this.dmy_title_b.addChild(this.m_epsodeTitle.exloader);
                  }
                  this.m_epsodeTitle.exloader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_LEFT);
                  this.m_epsodeTitle.isAttach = true;
                  _loc2_ = true;
               }
            }
            _loc3_ = 0;
            while(_loc3_ < 5)
            {
               _loc4_ = "mc_chap" + _loc3_;
               _loc5_ = getChildByName(_loc4_) as MovieClip;
               if(_loc5_)
               {
                  trace("m_name : " + _loc4_);
                  if(_loc3_ < this.m_resultDataNum)
                  {
                     if(Boolean(this.m_resultData[_loc3_].iconPlLoader.IsLoadedXfbin()) && Boolean(this.m_resultData[_loc3_].iconEnLoader.IsLoadedXfbin()))
                     {
                        if(this.m_resultData[_loc3_].isAttach == false)
                        {
                           if(this.m_resultData[_loc3_].isNoPlay == true)
                           {
                              _loc5_.gotoAndStop("btl_none");
                           }
                           _loc5_.dmy_char1.addChild(this.m_resultData[_loc3_].iconPlLoader);
                           this.m_resultData[_loc3_].iconPlLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                           _loc5_.dmy_char2.addChild(this.m_resultData[_loc3_].iconEnLoader);
                           this.m_resultData[_loc3_].iconEnLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                           this.m_resultData[_loc3_].isAttach = true;
                           _loc2_ = true;
                        }
                     }
                     else
                     {
                        _loc2_ = false;
                     }
                     _loc6_ = "";
                     if(this.m_resultData[_loc3_].isNoPlay == true)
                     {
                        _loc6_ = "none";
                     }
                     else
                     {
                        switch(this.m_resultData[_loc3_].rate)
                        {
                           case 0:
                              _loc6_ = "s";
                              break;
                           case 1:
                              _loc6_ = "a";
                              break;
                           case 2:
                              _loc6_ = "b";
                              break;
                           case 3:
                              _loc6_ = "c";
                              break;
                           case 4:
                              _loc6_ = "d";
                        }
                     }
                     _loc5_.mc_rate.gotoAndStop(_loc6_);
                     if(this.m_resultData[_loc3_].isRankUp == false)
                     {
                        _loc5_.mc_up.visible = false;
                     }
                     _loc7_ = "";
                     switch(this.m_resultData[_loc3_].battleType)
                     {
                        case 0:
                           _loc7_ = "boss";
                           break;
                        case 1:
                           _loc7_ = "free";
                           break;
                        case 2:
                           _loc7_ = "grp";
                           break;
                        case 3:
                           _loc7_ = "drm";
                     }
                     trace("BattaleType : " + _loc7_ + "  i : " + _loc3_);
                     _loc8_ = _loc5_.getChildByName("mc_btl") as MovieClip;
                     if(_loc8_)
                     {
                        _loc8_.gotoAndStop(_loc7_);
                     }
                     else
                     {
                        trace("no mc mc_btl");
                     }
                     _loc5_.txt_chap.SetText(this.m_resultData[_loc3_].chpterName);
                  }
                  else if(this.m_resultDataNum == _loc3_ && this.m_isNoPlayChapter == false)
                  {
                     trace("bouns bar");
                     _loc5_.gotoAndStop("bns");
                     _loc5_.mc_txtbar;
                     _loc5_.mc_txtbar.txt_rslt.SetText(ExternalInterface.call("MessageConvert","battleresult_005"));
                     _loc5_.mc_txtbar.txt_pt.SetText("");
                     _loc5_.mc_txtbar.txt_mult.SetText(" " + ExternalInterface.call("MessageConvert","battleresult_010"));
                     _loc5_.mc_txtbar.txt_money00.SetText("");
                     _loc9_ = "";
                     switch(this.GetTotalRank())
                     {
                        case 0:
                           _loc9_ = "1.5";
                           break;
                        case 1:
                           _loc9_ = "1.3";
                           break;
                        case 2:
                           _loc9_ = "1.2";
                           break;
                        case 3:
                           _loc9_ = "1.1";
                           break;
                        case 4:
                           _loc9_ = "1.0";
                     }
                     _loc5_.mc_txtbar.txt_money01.SetText(_loc9_);
                     _loc5_.mc_txtbar.txt_ryo.SetText("");
                  }
                  else
                  {
                     _loc5_.visible = false;
                  }
               }
               else
               {
                  trace("no mc_chap0" + _loc3_);
               }
               _loc3_++;
            }
            if(_loc2_)
            {
               this.m_allAttach = true;
               removeEventListener(Event.ENTER_FRAME,this.onEnterFrameLoadCheck);
            }
         }
      }
      
      public function EnablePad() : void
      {
         trace("EnablePad");
         this.m_inputPad.SetEnableLocal(true);
      }
      
      public function DisablePad() : void
      {
         trace("DisablePad");
         this.m_inputPad.SetEnableLocal(false);
      }
      
      public function SetUpKeyHelp() : void
      {
         trace("SetUpKeyHelp");
         if(this.m_keyHelp != null)
         {
            this.m_keyHelp.PopKeyHelp();
            if(this.m_step == STEP_IN)
            {
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_SKIP);
            }
            else
            {
               if(this.m_isDrawItemList == true)
               {
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_START,"battleresult_075");
               }
               this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_LEFT,"battleresult_071");
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_NEXT);
            }
            this.m_keyHelp.PushKeyHelp();
         }
      }
      
      public function SetStart() : void
      {
         this.m_step = STEP_IN;
         this.gotoAndPlay("in");
         this.play();
      }
      
      internal function frame77() : *
      {
         stop();
      }
   }
}

