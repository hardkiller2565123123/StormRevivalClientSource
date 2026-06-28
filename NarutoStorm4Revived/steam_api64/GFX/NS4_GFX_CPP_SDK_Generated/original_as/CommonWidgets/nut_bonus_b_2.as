package script.result_main
{
   import ELoader.ExtendLoader;
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import flash.net.URLRequest;
   import script.xcmn_btn_plat.smb_btn_key_lr;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol145")]
   public class nut_bonus_b extends MovieClip
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
      
      internal static const BONUS_MAX_NUM:Number = 4;
      
      public var mc_chap:MovieClip;
      
      public var mc_cursor_down:nut_cursor_m;
      
      public var mc_cursor_l:nut_cursor_m;
      
      public var mc_cursor_r:nut_cursor_m;
      
      public var mc_cursor_up:nut_cursor_m;
      
      public var mc_head:MovieClip;
      
      public var mc_icon_l:smb_btn_key_lr;
      
      public var mc_icon_r:smb_btn_key_lr;
      
      public var mc_txtbar_00:anm_textbar01;
      
      public var mc_txtbar_01:anm_textbar01;
      
      public var mc_txtbar_02:anm_textbar01;
      
      public var mc_txtbar_03:anm_textbar01;
      
      public var mc_txtbar_04:anm_textbar01;
      
      public var mc_txtbar_05:anm_textbar01;
      
      public var GetEpsodeData:Function;
      
      public var GetEpsodeDataNum:Function;
      
      public var SetDecide:Function;
      
      public var SetClosed:Function;
      
      private var m_step:int;
      
      private var m_Index:int;
      
      private var m_resultData:Array;
      
      private var m_resultDataNum:int;
      
      private var m_iaBarNo:int;
      
      private var m_saBarNo:int;
      
      private var m_continueBarNo:int;
      
      private var m_rankBarNo:int;
      
      private var m_TotalBarNo:int;
      
      private var m_hpMoeny:int;
      
      private var m_iaMoeny:int;
      
      private var m_saMoeny:int;
      
      private var m_noContinueMoeny:int;
      
      private var m_rankRate:Number;
      
      private var m_inputPad:InputPadKeyCode = null;
      
      private var m_keyHelp:KeyHelpCode = null;
      
      private var m_isTrail:Boolean;
      
      public function nut_bonus_b()
      {
         super();
         addFrameScript(5,this.frame6,9,this.frame10);
         this.m_step = STEP_NONE;
         this.m_Index = 0;
         this.m_resultDataNum = 0;
         this.m_iaBarNo = 0;
         this.m_saBarNo = 0;
         this.m_continueBarNo = 0;
         this.m_rankBarNo = 0;
         this.m_TotalBarNo = 0;
         this.m_hpMoeny = 0;
         this.m_iaMoeny = 0;
         this.m_saMoeny = 0;
         this.m_noContinueMoeny = 0;
         this.m_rankRate = 1;
         this.m_isTrail = false;
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
         this.m_isTrail = param1;
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
            this.m_resultData[_loc2_].hpBonus = 0;
            this.m_resultData[_loc2_].saMaxNum = 0;
            this.m_resultData[_loc2_].saClearNum = 0;
            this.m_resultData[_loc2_].setSABarNo = 0;
            this.m_resultData[_loc2_].iaMaxNum = 0;
            this.m_resultData[_loc2_].iaClearNum = 0;
            this.m_resultData[_loc2_].isRankUp = 0;
            this.m_resultData[_loc2_].isContinue = 0;
            this.m_resultData[_loc2_].setIABarNo = 0;
            this.m_resultData[_loc2_].setRateBarNo = 0;
            _loc2_++;
         }
         this.GetEpsodeData(this.m_resultData);
         this.RequestLoad();
         this.mc_cursor_up.visible = false;
         this.mc_cursor_down.visible = false;
         this.mc_cursor_l.visible = false;
         this.mc_icon_l.visible = false;
         if(this.m_resultDataNum <= 1)
         {
            this.mc_cursor_r.visible = false;
            this.mc_icon_r.visible = false;
         }
         this.mc_head.txt_head.SetText("");
         this.gotoAndPlay("in");
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc2_:uint = 0;
         switch(this.m_step)
         {
            case STEP_NONE:
               this.m_step = STEP_IN;
               trace("STEP_NONE");
               break;
            case STEP_IN:
               this.UpdataBar();
               this.m_step = STEP_IN_END;
               trace("STEP_IN");
               break;
            case STEP_IN_END:
               if(this.currentFrameLabel == "loop")
               {
                  this.mc_head.txt_head.SetText(ExternalInterface.call("MessageConvert","battleresult_071"));
                  this.UpdataBar();
                  this.SetUpKeyHelp();
                  this.m_step = STEP_IDLE;
                  trace("STEP_IN_END");
               }
               break;
            case STEP_IDLE:
               _loc2_ = this.m_inputPad.GetPadPress();
               if(this.m_inputPad.GetKeyInputBtn_Cancel() & _loc2_)
               {
                  this.m_keyHelp.PopKeyHelp();
                  this.m_step = STEP_CLOSE;
                  this.gotoAndPlay("out");
                  ExternalInterface.call("RequestPlaySE_Cancel");
               }
               if(this.m_inputPad.GetKeyInputBtn_L_Left() & _loc2_)
               {
                  if(this.m_Index > 0)
                  {
                     this.mc_cursor_r.visible = true;
                     this.mc_icon_r.visible = true;
                     this.DetachCharaIcon();
                     --this.m_Index;
                     if(this.m_Index <= 0)
                     {
                        this.m_Index = 0;
                        this.mc_cursor_l.visible = false;
                        this.mc_icon_l.visible = false;
                     }
                     this.UpdataBar();
                     ExternalInterface.call("RequestPlaySE_Select");
                  }
               }
               if(this.m_inputPad.GetKeyInputBtn_L_Right() & _loc2_)
               {
                  if(this.m_Index < this.m_resultDataNum - 1)
                  {
                     this.mc_cursor_l.visible = true;
                     this.mc_icon_l.visible = true;
                     this.DetachCharaIcon();
                     ++this.m_Index;
                     if(this.m_Index >= this.m_resultDataNum - 1)
                     {
                        this.m_Index = this.m_resultDataNum - 1;
                        this.mc_cursor_r.visible = false;
                        this.mc_icon_r.visible = false;
                     }
                     this.UpdataBar();
                     ExternalInterface.call("RequestPlaySE_Select");
                  }
               }
               break;
            case STEP_CLOSE:
               this.m_step = STEP_CLOSE_END;
               trace("STEP_CLOSE");
               break;
            case STEP_CLOSE_END:
               if(this.currentFrame == this.totalFrames)
               {
                  this.m_step = STEP_END;
                  trace("STEP_CLOSE_END");
                  this.SetClosed(true);
               }
               break;
            case STEP_END:
         }
         this.AttachCharaIcon();
      }
      
      public function UpdataBar() : void
      {
         var _loc2_:String = null;
         var _loc3_:Number = NaN;
         var _loc4_:String = null;
         var _loc5_:Array = null;
         var _loc6_:* = undefined;
         var _loc7_:String = null;
         var _loc8_:int = 0;
         var _loc9_:int = 0;
         var _loc10_:String = null;
         trace("UpdataBar");
         this.m_iaBarNo = 0;
         this.m_saBarNo = 0;
         this.m_continueBarNo = 0;
         this.m_rankBarNo = 0;
         this.m_TotalBarNo = 0;
         this.m_hpMoeny = 0;
         this.m_iaMoeny = 0;
         this.m_saMoeny = 0;
         this.m_noContinueMoeny = 0;
         this.m_rankRate = 1;
         var _loc1_:int = 0;
         while(_loc1_ < 6)
         {
            _loc2_ = "d";
            _loc3_ = 0;
            _loc4_ = "mc_txtbar_0" + _loc1_;
            _loc6_ = getChildByName(_loc4_) as MovieClip;
            if(_loc6_)
            {
               if(_loc6_.txt_pt)
               {
                  _loc6_.txt_pt.SetTextRubyEnable(false);
               }
               if(_loc6_.txt_mult)
               {
                  _loc6_.txt_mult.SetTextRubyEnable(false);
               }
               if(_loc6_.txt_money00)
               {
                  _loc6_.txt_money00.SetTextRubyEnable(false);
               }
               if(_loc6_.txt_money01)
               {
                  _loc6_.txt_money01.SetTextRubyEnable(false);
               }
               if(_loc6_.txt_ryo)
               {
                  _loc6_.txt_ryo.SetTextRubyEnable(false);
               }
               _loc6_.mc_rate.visible = true;
               _loc7_ = ExternalInterface.call("MessageConvert","battleresult_008");
               if(_loc1_ == 0)
               {
                  _loc6_.txt_rslt.SetText(ExternalInterface.call("MessageConvert","battleresult_002"));
                  _loc6_.txt_sf.SetText("");
                  _loc5_ = [this.m_resultData[this.m_Index].hpBonus];
                  _loc6_.txt_pt.SetText(ExternalInterface.call("MessageConvert","collection_004"));
                  _loc6_.txt_pt.ReplaceTextList(_loc5_);
                  _loc6_.txt_mult.SetText(ExternalInterface.call("MessageConvert","battleresult_010"));
                  _loc6_.txt_money00.SetText("100");
                  this.m_hpMoeny = this.m_resultData[this.m_Index].hpBonus * 100;
                  _loc6_.txt_money01.SetText(this.m_hpMoeny);
                  _loc6_.txt_ryo.SetText(_loc7_);
                  _loc3_ = Number(this.m_resultData[this.m_Index].hpBonus);
               }
               else
               {
                  _loc6_.visible = true;
                  _loc8_ = 100;
                  _loc9_ = 0;
                  if(this.m_resultData[this.m_Index].iaMaxNum > 0 && this.m_iaBarNo == 0)
                  {
                     trace("IA Bonus  i : " + _loc1_);
                     _loc6_.gotoAndStop("off");
                     _loc6_.txt_rslt.SetText(ExternalInterface.call("MessageConvert","battleresult_062"));
                     _loc9_ = this.m_resultData[this.m_Index].iaClearNum / this.m_resultData[this.m_Index].iaMaxNum * 100;
                     _loc5_.length = 0;
                     _loc5_.push(this.m_resultData[this.m_Index].iaClearNum);
                     _loc5_.push(this.m_resultData[this.m_Index].iaMaxNum);
                     _loc6_.txt_sf.SetText(ExternalInterface.call("MessageConvert","battleresult_076"));
                     _loc6_.txt_sf.ReplaceTextList(_loc5_);
                     _loc5_.length = 0;
                     _loc5_.push(_loc9_);
                     _loc6_.txt_pt.SetText(ExternalInterface.call("MessageConvert","collection_004"));
                     _loc6_.txt_pt.ReplaceTextList(_loc5_);
                     _loc6_.txt_mult.SetText(ExternalInterface.call("MessageConvert","battleresult_010"));
                     _loc6_.txt_money00.SetText(String(_loc8_));
                     this.m_iaMoeny = _loc8_ * _loc9_;
                     _loc6_.txt_money01.SetText(this.m_iaMoeny);
                     _loc6_.txt_ryo.SetText(_loc7_);
                     this.m_iaBarNo = _loc1_;
                     _loc3_ = this.m_resultData[this.m_Index].iaClearNum / this.m_resultData[this.m_Index].iaMaxNum * 100;
                  }
                  else if(this.m_resultData[this.m_Index].saMaxNum > 0 && this.m_saBarNo == 0)
                  {
                     trace("SA Bonus  i : " + _loc1_);
                     _loc6_.gotoAndStop("on");
                     _loc6_.txt_rslt.SetText(ExternalInterface.call("MessageConvert","battleresult_063"));
                     _loc9_ = this.m_resultData[this.m_Index].saClearNum / this.m_resultData[this.m_Index].saMaxNum * 100;
                     _loc5_.length = 0;
                     _loc5_.push(this.m_resultData[this.m_Index].saClearNum);
                     _loc5_.push(this.m_resultData[this.m_Index].saMaxNum);
                     _loc6_.txt_sf.SetText(ExternalInterface.call("MessageConvert","networkmode_228"));
                     _loc6_.txt_sf.ReplaceTextList(_loc5_);
                     _loc5_.length = 0;
                     _loc5_.push(_loc9_);
                     _loc6_.txt_pt.SetText(ExternalInterface.call("MessageConvert","collection_004"));
                     _loc6_.txt_pt.ReplaceTextList(_loc5_);
                     _loc6_.txt_mult.SetText(ExternalInterface.call("MessageConvert","battleresult_010"));
                     _loc6_.txt_money00.SetText(String(_loc8_));
                     this.m_saMoeny = _loc8_ * _loc9_;
                     _loc6_.txt_money01.SetText(this.m_saMoeny);
                     _loc6_.txt_ryo.SetText(_loc7_);
                     this.m_saBarNo = _loc1_;
                     _loc3_ = this.m_resultData[this.m_Index].saClearNum / this.m_resultData[this.m_Index].saMaxNum * 100;
                  }
                  else if(this.m_continueBarNo == 0 && this.m_isTrail == false)
                  {
                     trace("No Continue Bonus  i : " + _loc1_);
                     _loc6_.gotoAndStop("on");
                     _loc6_.txt_rslt.SetText(ExternalInterface.call("MessageConvert","MSG_demo_001"));
                     _loc6_.txt_sf.SetText("");
                     if(this.m_resultData[this.m_Index].isContinue == false)
                     {
                        _loc6_.txt_pt.SetText("");
                        _loc6_.txt_mult.SetText(ExternalInterface.call("MessageConvert","network_sys_013"));
                        _loc6_.txt_money00.SetText("");
                        this.m_noContinueMoeny = 10000;
                        _loc3_ = 100;
                     }
                     else
                     {
                        _loc6_.txt_pt.SetText("");
                        _loc6_.txt_mult.SetText(ExternalInterface.call("MessageConvert","network_sys_012"));
                        _loc6_.txt_money00.SetText("");
                        this.m_noContinueMoeny = 0;
                        _loc3_ = 0;
                     }
                     _loc6_.txt_money01.SetText(this.m_noContinueMoeny);
                     _loc6_.txt_ryo.SetText(_loc7_);
                     this.m_continueBarNo = _loc1_;
                  }
                  else if(this.m_rankBarNo == 0)
                  {
                     trace("rank Bonus  i : " + _loc1_);
                     _loc6_.gotoAndStop("off");
                     _loc6_.txt_rslt.SetText(ExternalInterface.call("MessageConvert","battleresult_005"));
                     _loc6_.txt_sf.SetText("");
                     _loc6_.txt_pt.SetText("");
                     _loc6_.txt_mult.SetText(" " + ExternalInterface.call("MessageConvert","battleresult_010"));
                     _loc6_.txt_money00.SetText("");
                     _loc10_ = "";
                     switch(this.m_resultData[this.m_Index].rate)
                     {
                        case 4:
                           _loc10_ = "1.0";
                           this.m_rankRate = 1;
                           _loc3_ = 0;
                           break;
                        case 3:
                           _loc10_ = "1.1";
                           this.m_rankRate = 1.1;
                           _loc3_ = 20;
                           break;
                        case 2:
                           _loc10_ = "1.2";
                           this.m_rankRate = 1.2;
                           _loc3_ = 50;
                           break;
                        case 1:
                           _loc10_ = "1.3";
                           this.m_rankRate = 1.3;
                           _loc3_ = 80;
                           break;
                        case 0:
                           _loc10_ = "1.5";
                           this.m_rankRate = 1.5;
                           _loc3_ = 100;
                     }
                     _loc6_.txt_money01.SetText(_loc10_);
                     _loc6_.txt_ryo.SetText("");
                     this.m_rankBarNo = _loc1_;
                  }
                  else if(this.m_TotalBarNo == 0)
                  {
                     trace("rank Bonus  i : " + _loc1_);
                     _loc6_.gotoAndStop("off");
                     _loc6_.txt_sf.SetText("");
                     _loc6_.txt_pt.SetText(" ");
                     _loc6_.txt_mult.SetText(" ");
                     _loc6_.txt_money00.SetText(" ");
                     _loc6_.txt_rslt.SetText(String(ExternalInterface.call("MessageConvert","battleresult_007")));
                     _loc8_ = 0;
                     _loc8_ = (this.m_hpMoeny + this.m_iaMoeny + this.m_saMoeny + this.m_noContinueMoeny) * this.m_rankRate;
                     _loc6_.txt_money01.SetText(_loc8_);
                     _loc6_.txt_ryo.SetText(_loc7_);
                     _loc6_.mc_rate.visible = false;
                     this.m_TotalBarNo = _loc1_;
                  }
                  else
                  {
                     _loc6_.visible = false;
                  }
               }
               if(_loc3_ >= 90)
               {
                  _loc2_ = "s";
               }
               else if(_loc3_ < 90 && _loc3_ >= 80)
               {
                  _loc2_ = "a";
               }
               else if(_loc3_ < 80 && _loc3_ >= 50)
               {
                  _loc2_ = "b";
               }
               else if(_loc3_ < 50 && _loc3_ >= 20)
               {
                  _loc2_ = "c";
               }
               else
               {
                  _loc2_ = "d";
               }
               _loc6_.mc_rate.gotoAndStop(_loc2_);
            }
            else
            {
               trace("no mc_txbar  name:" + _loc4_);
            }
            _loc1_++;
         }
      }
      
      public function RequestLoad() : void
      {
         var _loc1_:URLRequest = null;
         trace("RequestLoad");
         var _loc2_:int = 0;
         while(_loc2_ < this.m_resultDataNum)
         {
            _loc1_ = null;
            _loc1_ = new URLRequest("../charicon_vs/vs_" + this.m_resultData[_loc2_].playerIcon + ".xfbin");
            this.m_resultData[_loc2_].iconPlLoader.load(_loc1_);
            _loc1_ = null;
            _loc1_ = new URLRequest("../charicon_vs/vs_" + this.m_resultData[_loc2_].enemyIcon + ".xfbin");
            this.m_resultData[_loc2_].iconEnLoader.load(_loc1_);
            _loc2_++;
         }
      }
      
      public function AttachCharaIcon() : void
      {
         var _loc4_:* = undefined;
         var _loc5_:* = undefined;
         var _loc1_:Boolean = true;
         var _loc2_:* = "mc_chap";
         var _loc3_:* = getChildByName(_loc2_) as MovieClip;
         if(_loc3_)
         {
            if(this.m_resultData[this.m_Index].isAttach == false)
            {
               if(Boolean(this.m_resultData[this.m_Index].iconPlLoader.IsLoadedXfbin()) && Boolean(this.m_resultData[this.m_Index].iconEnLoader.IsLoadedXfbin()))
               {
                  if(_loc3_.dmy_char1)
                  {
                     _loc3_.dmy_char1.addChild(this.m_resultData[this.m_Index].iconPlLoader);
                     this.m_resultData[this.m_Index].iconPlLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                  }
                  else
                  {
                     trace(" # nut_bonus_b AttachCharaIcon dmy_char1 ");
                  }
                  if(_loc3_.dmy_char2)
                  {
                     _loc3_.dmy_char2.addChild(this.m_resultData[this.m_Index].iconEnLoader);
                     this.m_resultData[this.m_Index].iconEnLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
                  }
                  else
                  {
                     trace(" # nut_bonus_b AttachCharaIcon dmy_char2 ");
                  }
                  this.m_resultData[this.m_Index].isAttach = true;
                  _loc1_ = false;
               }
            }
            _loc4_ = "";
            switch(this.m_resultData[this.m_Index].rate)
            {
               case 0:
                  _loc4_ = "s";
                  break;
               case 1:
                  _loc4_ = "a";
                  break;
               case 2:
                  _loc4_ = "b";
                  break;
               case 3:
                  _loc4_ = "c";
                  break;
               case 4:
                  _loc4_ = "d";
            }
            if(_loc3_.mc_rate)
            {
               _loc3_.mc_rate.gotoAndStop(_loc4_);
            }
            else
            {
               trace(" # nut_bonus_b AttachCharaIcon mc_chap.mc_rate ");
            }
            if(this.m_resultData[this.m_Index].isRankUp)
            {
               _loc3_.mc_up.visible = true;
            }
            else
            {
               _loc3_.mc_up.visible = false;
            }
            _loc5_ = "";
            switch(this.m_resultData[this.m_Index].battleType)
            {
               case 0:
                  _loc5_ = "boss";
                  break;
               case 1:
                  _loc5_ = "free";
                  break;
               case 2:
                  _loc5_ = "grp";
                  break;
               case 3:
                  _loc5_ = "drm";
            }
            if(_loc3_.mc_btl)
            {
               _loc3_.mc_btl.gotoAndStop(_loc5_);
            }
            else
            {
               trace(" # nut_bonus_b AttachCharaIcon mc_chap.mc_btl ");
            }
            if(_loc3_.txt_chap)
            {
               _loc3_.txt_chap.SetText(this.m_resultData[this.m_Index].chpterName);
            }
            else
            {
               trace(" # nut_bonus_b AttachCharaIcon mc_chap.txt_chap ");
            }
         }
      }
      
      public function DetachCharaIcon() : void
      {
         if(this.m_resultData[this.m_Index].isAttach == true)
         {
            this.m_resultData[this.m_Index].iconPlLoader.RemoveToParent();
            this.m_resultData[this.m_Index].iconEnLoader.RemoveToParent();
            this.m_resultData[this.m_Index].isAttach = false;
         }
      }
      
      public function SetUpKeyHelp() : void
      {
         trace("SetUpKeyHelp");
         if(this.m_keyHelp != null)
         {
            this.m_keyHelp.PopKeyHelp();
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_CLOSE2);
            this.m_keyHelp.PushKeyHelp();
         }
      }
      
      internal function frame6() : *
      {
         this.stop();
      }
      
      internal function frame10() : *
      {
         this.stop();
      }
   }
}

