package script.duel_boss_help
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.geom.Point;
   import script.duel_boss.*;
   import script.xcmn_font.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class nut_help_b extends MovieClip
   {
      
      private static const CCD_HELP_MSG_ENABLE:String = "commandlist_demo_19";
      
      private static const CCD_HELP_MSG_DISABLE:String = "commandlist_demo_20";
      
      private static const CCD_HELP_MSG_START_ENABLE:String = "commandlist_demo_19";
      
      private static const CCD_HELP_MSG_START_DISABLE:String = "commandlist_demo_20";
      
      private static const CCD_HELP_MSG_MARGIN_X:Number = 10;
      
      private static const CCD_HELP_MSG_WIDTH:Number = 300;
      
      private static const CCD_HELP_MSG_PHASE_1:uint = 0;
      
      private static const CCD_HELP_MSG_PHASE_2:uint = 1;
      
      private static const CCD_HELP_MSG_PHASE_4:uint = 2;
      
      private static const CCD_HELP_MSG_BOSS4_PHASE_1:uint = 3;
      
      private static const CCD_HELP_MSG_BOSS4_PHASE_2:uint = 4;
      
      private static const CCD_TEXT_COLOR_BASE:uint = smb_font.CCD_COLOR_WHITE;
      
      private static const CCD_TEXT_COLOR_PICK_UP:uint = smb_font.CCD_COLOR_RED;
      
      public var mc_pick:MovieClip;
      
      public var txt_act:smb_font;
      
      public var txt_hlp:smb_font;
      
      public var txt_key:smb_font;
      
      private var m_phase01MsgTbl:nut_help_phase01 = new nut_help_phase01();
      
      private var m_phase02MsgTbl:nut_help_phase02 = new nut_help_phase02();
      
      private var m_phase04MsgTbl:nut_help_phase04 = new nut_help_phase04();
      
      private var m_boss04phase01MsgTbl:nut_help_boss04phase01 = new nut_help_boss04phase01();
      
      private var m_boss04phase02MsgTbl:nut_help_boss04phase02 = new nut_help_boss04phase02();
      
      private var m_boss13phase01MsgTbl:nut_help_boss13phase01 = new nut_help_boss13phase01();
      
      private var m_msg:Array = new Array();
      
      private var m_cmd:Array = new Array();
      
      private var m_pickUp:MovieClip;
      
      private var m_help:smb_font;
      
      private var m_safeFrameRight:Number = 1536;
      
      private var m_isSetUpMsg:Boolean = false;
      
      private var m_setUpPhase:uint = 0;
      
      private var m_isChangeColor:Boolean = false;
      
      private var m_enableHelpMsg:Boolean = false;
      
      private var m_isStartBtnChangeEnable:Boolean = false;
      
      public function nut_help_b()
      {
         super();
         addFrameScript(0,this.frame1);
         var _loc1_:smb_font = smb_font(getChildByName("txt_act"));
         if(_loc1_)
         {
            _loc1_.SetText("");
         }
         var _loc2_:smb_font = smb_font(getChildByName("txt_key"));
         if(_loc2_)
         {
            _loc2_.SetText("");
         }
         var _loc3_:smb_font = smb_font(getChildByName("txt_hlp"));
         if(_loc3_)
         {
            _loc3_.SetText("");
         }
      }
      
      public function Initialize() : *
      {
         var _loc1_:Number = Number(ExternalInterface.call("GetSafeFrameRate"));
         if(_loc1_ != 0)
         {
            this.m_safeFrameRight = this.stage.stageWidth * (1 - _loc1_) * 0.5;
            this.m_safeFrameRight = this.stage.stageWidth - this.m_safeFrameRight;
            trace("StageWidth:" + this.stage.stageWidth);
            trace("SafeFrameRight:" + this.m_safeFrameRight);
         }
         this.m_msg.push(smb_font(getChildByName("txt_act")));
         this.m_msg[0].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         this.m_msg[0].SetTextAutoSize();
         this.m_msg[0].SetTextRubyEnable(false);
         this.m_cmd.push(smb_font(getChildByName("txt_key")));
         this.m_cmd[0].SetTextAlign(smb_font.CCD_ALIGN_LEFT);
         this.m_cmd[0].SetTextAutoSize();
         this.m_cmd[0].SetTextRubyEnable(false);
         this.m_help = smb_font(getChildByName("txt_hlp"));
         this.m_help.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         this.m_help.SetTextRubyEnable(false);
         this.m_help.SetText(String(ExternalInterface.call("MessageConvert",this.m_isStartBtnChangeEnable == true ? CCD_HELP_MSG_START_ENABLE : CCD_HELP_MSG_ENABLE)));
         var _loc2_:MovieClip = MovieClip(getChildByName("mc_pick"));
         _loc2_.visible = false;
      }
      
      public function SetStartBtnChangeEnable(param1:Boolean) : *
      {
         this.m_isStartBtnChangeEnable = param1;
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         visible = param1;
      }
      
      public function ChangeVisibleHelpMsg(param1:Boolean) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < this.m_msg.length)
         {
            this.m_msg[_loc2_].visible = param1;
            _loc2_++;
         }
         _loc2_ = 0;
         while(_loc2_ < this.m_cmd.length)
         {
            this.m_cmd[_loc2_].visible = param1;
            _loc2_++;
         }
         if(param1 == true)
         {
            this.m_help.SetText(String(ExternalInterface.call("MessageConvert",this.m_isStartBtnChangeEnable == true ? CCD_HELP_MSG_START_ENABLE : CCD_HELP_MSG_ENABLE)));
         }
         else
         {
            this.m_help.SetText(String(ExternalInterface.call("MessageConvert",this.m_isStartBtnChangeEnable == true ? CCD_HELP_MSG_START_DISABLE : CCD_HELP_MSG_DISABLE)));
         }
      }
      
      public function SetupHelpMenuPhase1() : *
      {
         var _loc6_:Number = NaN;
         trace("Phase1Msg");
         var _loc1_:int = 1;
         while(_loc1_ < this.m_msg.length)
         {
            removeChild(this.m_msg[_loc1_]);
            removeChild(this.m_cmd[_loc1_]);
            _loc1_++;
         }
         this.m_msg.length = 1;
         this.m_cmd.length = 1;
         var _loc2_:Number = 0;
         var _loc3_:Number = 0;
         var _loc4_:uint = nut_help_phase01.CCD_HELP_NUM - 1;
         _loc1_ = 0;
         while(_loc1_ < nut_help_phase01.CCD_HELP_NUM)
         {
            if(_loc1_ >= 1)
            {
               this.m_msg.push(new smb_font());
               this.m_msg[_loc1_].SetTextSize(23);
               this.m_msg[_loc1_].SetTextPivot(this.m_msg[0].GetTextPivot());
               this.m_msg[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
               this.m_msg[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_msg[_loc1_]);
               this.m_cmd.push(new smb_font());
               this.m_cmd[_loc1_].SetTextSize(23);
               this.m_cmd[_loc1_].SetTextPivot(this.m_cmd[0].GetTextPivot());
               this.m_cmd[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_LEFT);
               this.m_cmd[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_cmd[_loc1_]);
            }
            if(this.m_help.IsArabic() == false)
            {
               this.m_msg[_loc1_].SetText(this.m_phase01MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_cmd[_loc1_].SetText(this.m_phase01MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            else
            {
               this.m_cmd[_loc1_].SetText(this.m_phase01MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_msg[_loc1_].SetText(this.m_phase01MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            trace(this.m_cmd[_loc1_]);
            if(this.m_cmd[_loc1_].GetTextFieldWidth() >= _loc2_)
            {
               _loc2_ = Number(this.m_cmd[_loc1_].GetTextFieldWidth());
            }
            _loc6_ = this.m_cmd[_loc1_].GetTextFieldHeight() > this.m_msg[_loc1_].GetTextFieldHeight() ? Number(this.m_cmd[_loc1_].GetTextFieldHeight()) : Number(this.m_msg[_loc1_].GetTextFieldHeight());
            if(_loc6_ > _loc3_)
            {
               _loc3_ = _loc6_;
            }
            _loc1_++;
         }
         var _loc5_:Point = new Point(0,0);
         this.m_cmd[0].GetTextPos(_loc5_);
         _loc1_ = 0;
         while(_loc1_ < this.m_msg.length)
         {
            this.m_cmd[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x,_loc5_.y - _loc3_ * _loc1_);
            this.m_msg[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x - CCD_HELP_MSG_MARGIN_X,_loc5_.y - _loc3_ * _loc1_);
            _loc1_++;
         }
         this.m_setUpPhase = CCD_HELP_MSG_PHASE_1;
      }
      
      public function SetupHelpMenuPhase2() : *
      {
      }
      
      public function SetupHelpMenuPhase4() : *
      {
         var _loc6_:Number = NaN;
         trace("Phase4Msg");
         var _loc1_:int = 1;
         while(_loc1_ < this.m_msg.length)
         {
            removeChild(this.m_msg[_loc1_]);
            removeChild(this.m_cmd[_loc1_]);
            _loc1_++;
         }
         this.m_msg.length = 1;
         this.m_cmd.length = 1;
         var _loc2_:Number = 0;
         var _loc3_:Number = 0;
         var _loc4_:uint = nut_help_phase04.CCD_HELP_NUM - 1;
         _loc1_ = 0;
         while(_loc1_ < nut_help_phase04.CCD_HELP_NUM)
         {
            if(_loc1_ >= 1)
            {
               this.m_msg.push(new smb_font());
               this.m_msg[_loc1_].SetTextSize(23);
               this.m_msg[_loc1_].SetTextPivot(this.m_msg[0].GetTextPivot());
               this.m_msg[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
               this.m_msg[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_msg[_loc1_]);
               this.m_cmd.push(new smb_font());
               this.m_cmd[_loc1_].SetTextSize(23);
               this.m_cmd[_loc1_].SetTextPivot(this.m_cmd[0].GetTextPivot());
               this.m_cmd[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_LEFT);
               this.m_cmd[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_cmd[_loc1_]);
            }
            if(this.m_help.IsArabic() == false)
            {
               this.m_msg[_loc1_].SetText(this.m_phase04MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_cmd[_loc1_].SetText(this.m_phase04MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            else
            {
               this.m_cmd[_loc1_].SetText(this.m_phase04MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_msg[_loc1_].SetText(this.m_phase04MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            if(this.m_cmd[_loc1_].GetTextFieldWidth() >= _loc2_)
            {
               _loc2_ = Number(this.m_cmd[_loc1_].GetTextFieldWidth());
            }
            _loc6_ = this.m_cmd[_loc1_].GetTextFieldHeight() > this.m_msg[_loc1_].GetTextFieldHeight() ? Number(this.m_cmd[_loc1_].GetTextFieldHeight()) : Number(this.m_msg[_loc1_].GetTextFieldHeight());
            if(_loc6_ > _loc3_)
            {
               _loc3_ = _loc6_;
            }
            _loc1_++;
         }
         var _loc5_:Point = new Point(0,0);
         this.m_cmd[0].GetTextPos(_loc5_);
         _loc1_ = 0;
         while(_loc1_ < this.m_msg.length)
         {
            this.m_cmd[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x,_loc5_.y - _loc3_ * _loc1_);
            this.m_msg[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x - CCD_HELP_MSG_MARGIN_X,_loc5_.y - _loc3_ * _loc1_);
            _loc1_++;
         }
         this.m_setUpPhase = CCD_HELP_MSG_PHASE_4;
      }
      
      public function SetupHelpMenuBoss04Phase1() : *
      {
         var _loc6_:Number = NaN;
         trace("Phase4Msg");
         var _loc1_:int = 1;
         while(_loc1_ < this.m_msg.length)
         {
            removeChild(this.m_msg[_loc1_]);
            removeChild(this.m_cmd[_loc1_]);
            _loc1_++;
         }
         this.m_msg.length = 1;
         this.m_cmd.length = 1;
         var _loc2_:Number = 0;
         var _loc3_:Number = 0;
         var _loc4_:uint = nut_help_boss04phase01.CCD_HELP_NUM - 1;
         _loc1_ = 0;
         while(_loc1_ < nut_help_boss04phase01.CCD_HELP_NUM)
         {
            if(_loc1_ >= 1)
            {
               this.m_msg.push(new smb_font());
               this.m_msg[_loc1_].SetTextSize(23);
               this.m_msg[_loc1_].SetTextPivot(this.m_msg[0].GetTextPivot());
               this.m_msg[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
               this.m_msg[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_msg[_loc1_]);
               this.m_cmd.push(new smb_font());
               this.m_cmd[_loc1_].SetTextSize(23);
               this.m_cmd[_loc1_].SetTextPivot(this.m_cmd[0].GetTextPivot());
               this.m_cmd[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_LEFT);
               this.m_cmd[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_cmd[_loc1_]);
            }
            if(this.m_help.IsArabic() == false)
            {
               this.m_msg[_loc1_].SetText(this.m_boss04phase01MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_cmd[_loc1_].SetText(this.m_boss04phase01MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            else
            {
               this.m_cmd[_loc1_].SetText(this.m_boss04phase01MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_msg[_loc1_].SetText(this.m_boss04phase01MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            if(this.m_cmd[_loc1_].GetTextFieldWidth() >= _loc2_)
            {
               _loc2_ = Number(this.m_cmd[_loc1_].GetTextFieldWidth());
            }
            _loc6_ = this.m_cmd[_loc1_].GetTextFieldHeight() > this.m_msg[_loc1_].GetTextFieldHeight() ? Number(this.m_cmd[_loc1_].GetTextFieldHeight()) : Number(this.m_msg[_loc1_].GetTextFieldHeight());
            if(_loc6_ > _loc3_)
            {
               _loc3_ = _loc6_;
            }
            _loc1_++;
         }
         var _loc5_:Point = new Point(0,0);
         this.m_cmd[0].GetTextPos(_loc5_);
         _loc1_ = 0;
         while(_loc1_ < this.m_msg.length)
         {
            this.m_cmd[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x,_loc5_.y - _loc3_ * _loc1_);
            this.m_msg[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x - CCD_HELP_MSG_MARGIN_X,_loc5_.y - _loc3_ * _loc1_);
            _loc1_++;
         }
         this.m_setUpPhase = CCD_HELP_MSG_BOSS4_PHASE_1;
      }
      
      public function SetupHelpMenuBoss04Phase2() : *
      {
         var _loc6_:Number = NaN;
         trace("Phase4Msg");
         var _loc1_:int = 1;
         while(_loc1_ < this.m_msg.length)
         {
            removeChild(this.m_msg[_loc1_]);
            removeChild(this.m_cmd[_loc1_]);
            _loc1_++;
         }
         this.m_msg.length = 1;
         this.m_cmd.length = 1;
         var _loc2_:Number = 0;
         var _loc3_:Number = 0;
         var _loc4_:uint = nut_help_boss04phase02.CCD_HELP_NUM - 1;
         _loc1_ = 0;
         while(_loc1_ < nut_help_boss04phase02.CCD_HELP_NUM)
         {
            if(_loc1_ >= 1)
            {
               this.m_msg.push(new smb_font());
               this.m_msg[_loc1_].SetTextSize(23);
               this.m_msg[_loc1_].SetTextPivot(this.m_msg[0].GetTextPivot());
               this.m_msg[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
               this.m_msg[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_msg[_loc1_]);
               this.m_cmd.push(new smb_font());
               this.m_cmd[_loc1_].SetTextSize(23);
               this.m_cmd[_loc1_].SetTextPivot(this.m_cmd[0].GetTextPivot());
               this.m_cmd[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_LEFT);
               this.m_cmd[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_cmd[_loc1_]);
            }
            if(this.m_help.IsArabic() == false)
            {
               this.m_msg[_loc1_].SetText(this.m_boss04phase02MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_cmd[_loc1_].SetText(this.m_boss04phase02MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            else
            {
               this.m_cmd[_loc1_].SetText(this.m_boss04phase02MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_msg[_loc1_].SetText(this.m_boss04phase02MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            if(this.m_cmd[_loc1_].GetTextFieldWidth() >= _loc2_)
            {
               _loc2_ = Number(this.m_cmd[_loc1_].GetTextFieldWidth());
            }
            _loc6_ = this.m_cmd[_loc1_].GetTextFieldHeight() > this.m_msg[_loc1_].GetTextFieldHeight() ? Number(this.m_cmd[_loc1_].GetTextFieldHeight()) : Number(this.m_msg[_loc1_].GetTextFieldHeight());
            if(_loc6_ > _loc3_)
            {
               _loc3_ = _loc6_;
            }
            _loc1_++;
         }
         var _loc5_:Point = new Point(0,0);
         this.m_cmd[0].GetTextPos(_loc5_);
         _loc1_ = 0;
         while(_loc1_ < this.m_msg.length)
         {
            this.m_cmd[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x,_loc5_.y - _loc3_ * _loc1_);
            this.m_msg[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x - CCD_HELP_MSG_MARGIN_X,_loc5_.y - _loc3_ * _loc1_);
            _loc1_++;
         }
         this.m_setUpPhase = CCD_HELP_MSG_BOSS4_PHASE_2;
      }
      
      public function SetupHelpMenuBoss13Phase1() : *
      {
         var _loc6_:Number = NaN;
         trace("Boss13Phase1Msg");
         var _loc1_:int = 1;
         while(_loc1_ < this.m_msg.length)
         {
            removeChild(this.m_msg[_loc1_]);
            removeChild(this.m_cmd[_loc1_]);
            _loc1_++;
         }
         this.m_msg.length = 1;
         this.m_cmd.length = 1;
         var _loc2_:Number = 0;
         var _loc3_:Number = 0;
         var _loc4_:uint = nut_help_boss13phase01.CCD_HELP_NUM - 1;
         _loc1_ = 0;
         while(_loc1_ < nut_help_boss13phase01.CCD_HELP_NUM)
         {
            if(_loc1_ >= 1)
            {
               this.m_msg.push(new smb_font());
               this.m_msg[_loc1_].SetTextSize(23);
               this.m_msg[_loc1_].SetTextPivot(this.m_msg[0].GetTextPivot());
               this.m_msg[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
               this.m_msg[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_msg[_loc1_]);
               this.m_cmd.push(new smb_font());
               this.m_cmd[_loc1_].SetTextSize(23);
               this.m_cmd[_loc1_].SetTextPivot(this.m_cmd[0].GetTextPivot());
               this.m_cmd[_loc1_].SetTextAlign(smb_font.CCD_ALIGN_LEFT);
               this.m_cmd[_loc1_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
               addChild(this.m_cmd[_loc1_]);
            }
            if(this.m_help.IsArabic() == false)
            {
               this.m_msg[_loc1_].SetText(this.m_boss13phase01MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_cmd[_loc1_].SetText(this.m_boss13phase01MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            else
            {
               this.m_cmd[_loc1_].SetText(this.m_boss13phase01MsgTbl.GetMessage(_loc4_ - _loc1_));
               this.m_msg[_loc1_].SetText(this.m_boss13phase01MsgTbl.GetCommand(_loc4_ - _loc1_));
            }
            trace(this.m_cmd[_loc1_]);
            if(this.m_cmd[_loc1_].GetTextFieldWidth() >= _loc2_)
            {
               _loc2_ = Number(this.m_cmd[_loc1_].GetTextFieldWidth());
            }
            _loc6_ = this.m_cmd[_loc1_].GetTextFieldHeight() > this.m_msg[_loc1_].GetTextFieldHeight() ? Number(this.m_cmd[_loc1_].GetTextFieldHeight()) : Number(this.m_msg[_loc1_].GetTextFieldHeight());
            if(_loc6_ > _loc3_)
            {
               _loc3_ = _loc6_;
            }
            _loc1_++;
         }
         var _loc5_:Point = new Point(0,0);
         this.m_cmd[0].GetTextPos(_loc5_);
         _loc1_ = 0;
         while(_loc1_ < this.m_msg.length)
         {
            this.m_cmd[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x,_loc5_.y - _loc3_ * _loc1_);
            this.m_msg[_loc1_].SetTextPos(this.m_safeFrameRight - _loc2_ - x - CCD_HELP_MSG_MARGIN_X,_loc5_.y - _loc3_ * _loc1_);
            _loc1_++;
         }
         this.m_setUpPhase = CCD_HELP_MSG_PHASE_1;
      }
      
      public function InitializeCameraHelp(param1:int) : *
      {
         var _loc2_:smb_font = null;
         gotoAndStop(1);
         this.m_help = smb_font(getChildByName("txt_hlp"));
         this.m_help.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         this.m_help.SetTextRubyEnable(false);
         if(param1)
         {
            this.m_help.SetText(String(ExternalInterface.call("MessageConvert","boss_helpcommand_002")));
         }
         else
         {
            this.m_help.SetText(String(ExternalInterface.call("MessageConvert","boss_helpcommand_001")));
         }
         this.m_help.ChangeBitmapDraw();
         _loc2_ = smb_font(getChildByName("txt_act"));
         _loc2_.visible = false;
         _loc2_ = smb_font(getChildByName("txt_key"));
         _loc2_.visible = false;
      }
      
      public function SetAlpha(param1:Number) : *
      {
         alpha = param1;
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_hlp.SetTextSize(23);
         this.txt_hlp.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_hlp.SetTextFit(true);
         this.txt_hlp.SetTextFieldWidth(500);
         this.txt_act.SetTextSize(23);
         this.txt_act.SetTextPivot(smb_font.CCD_PIVOT_RB);
         this.txt_act.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_key.SetTextSize(23);
         this.txt_key.SetTextPivot(smb_font.CCD_PIVOT_LB);
         this.txt_key.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

