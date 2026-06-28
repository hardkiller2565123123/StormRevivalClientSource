package script.stagesel
{
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class nut_stage_image extends MovieClip
   {
      
      public static const CCD_STAGE_NUM:Number = 43;
      
      public static const CCD_STAGE_IMAGE:String = "mc_stage_image";
      
      public static const CCD_STAGE_NUM_TBL_WIDTH:Number = 10;
      
      public static const CCD_STAGE_NUM_TBL_HEIGHT:Number = 5;
      
      public static const CCD_STAGE_NUM_TBL_WIDTH_OFFSET:Number = 3;
      
      public static const CCD_STAGE_SEL_WIDTH_OFFSET_LEFT:Number = 4;
      
      public static const CCD_STAGE_SEL_WIDTH_OFFSET_CENTER:Number = 6;
      
      public static const CCD_STAGE_RTB_ADD_CONTENTS_NUM:Number = 3;
      
      public var mc_stage_image00:MovieClip;
      
      public var mc_stage_image01:MovieClip;
      
      public var mc_stage_image02:MovieClip;
      
      public var mc_stage_image03:MovieClip;
      
      public var mc_stage_image04:MovieClip;
      
      public var mc_stage_image05:MovieClip;
      
      public var mc_stage_image06:MovieClip;
      
      public var mc_stage_image07:MovieClip;
      
      public var mc_stage_image08:MovieClip;
      
      public var mc_stage_image09:MovieClip;
      
      public var mc_stage_image10:MovieClip;
      
      public var mc_stage_image11:MovieClip;
      
      public var mc_stage_image12:MovieClip;
      
      public var mc_stage_image13:MovieClip;
      
      public var mc_stage_image14:MovieClip;
      
      public var mc_stage_image15:MovieClip;
      
      public var mc_stage_image16:MovieClip;
      
      public var mc_stage_image17:MovieClip;
      
      public var mc_stage_image18:MovieClip;
      
      public var mc_stage_image19:MovieClip;
      
      public var mc_stage_image20:MovieClip;
      
      public var mc_stage_image21:MovieClip;
      
      public var mc_stage_image22:MovieClip;
      
      public var mc_stage_image23:MovieClip;
      
      public var mc_stage_image24:MovieClip;
      
      public var mc_stage_image25:MovieClip;
      
      public var mc_stage_image26:MovieClip;
      
      public var mc_stage_image27:MovieClip;
      
      public var mc_stage_image28:MovieClip;
      
      public var mc_stage_image29:MovieClip;
      
      public var mc_stage_image30:MovieClip;
      
      public var mc_stage_image31:MovieClip;
      
      public var mc_stage_image32:MovieClip;
      
      public var mc_stage_image33:MovieClip;
      
      public var mc_stage_image34:MovieClip;
      
      public var mc_stage_image35:MovieClip;
      
      public var mc_stage_image36:MovieClip;
      
      public var mc_stage_image37:MovieClip;
      
      public var mc_stage_image38:MovieClip;
      
      public var mc_stage_image39:MovieClip;
      
      public var mc_stage_image40:MovieClip;
      
      public var mc_stage_image41:MovieClip;
      
      public var mc_stage_image42:MovieClip;
      
      public var SetStageNum:Function;
      
      public var SetDecide:Function;
      
      public var SetCancel:Function;
      
      private var m_oldSelectY:Number;
      
      private var m_inputPad:InputPadKeyCode;
      
      private var m_selectX:UiSelect;
      
      private var m_selectY:UiSelect;
      
      private var m_stageNum:Number;
      
      private var m_stageNumTbl:Array = [[0,1,2,3,4,5,6,7,8,9],[10,11,12,13,14,15,16,17,18,19],[20,21,22,23,24,25,26,27,28,29],[30,31,32,33,34,35,36,37,38,39],[40,41,42]];
      
      private var m_randCount:Number;
      
      private var m_isNetworkMode:Boolean = false;
      
      private var m_isClient:Boolean = false;
      
      private var m_isBanCancel:Boolean = false;
      
      private var m_isInstall:Boolean = false;
      
      private var m_isPushKeyHelp:Boolean = false;
      
      private var m_keyHelp:KeyHelpCode;
      
      private var m_isDisableRtbContents:Boolean = false;
      
      public function nut_stage_image()
      {
         super();
         addFrameScript(0,this.frame1);
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      public function OnRemove(param1:Event) : *
      {
         if(this.m_isPushKeyHelp == true)
         {
            this.m_keyHelp.PopKeyHelp();
            this.m_isPushKeyHelp = false;
         }
      }
      
      public function Initialize(param1:Boolean) : *
      {
         this.m_isNetworkMode = param1;
         this.m_inputPad = new InputPadKeyCode();
         this.m_selectX = new UiSelect();
         this.m_selectY = new UiSelect();
         this.m_selectX.InitSelect(0,0,CCD_STAGE_NUM_TBL_WIDTH - 1,this.m_inputPad.GetKeyInputBtn_L_Left(),this.m_inputPad.GetKeyInputBtn_L_Right(),UiSelect.CCD_LOOP_TYPE_PUSH);
         this.m_selectY.InitSelect(0,0,CCD_STAGE_NUM_TBL_HEIGHT - 1,this.m_inputPad.GetKeyInputBtn_L_Up(),this.m_inputPad.GetKeyInputBtn_L_Down(),UiSelect.CCD_LOOP_TYPE_PUSH);
         this.m_oldSelectY = 0;
         var _loc2_:Number = 0;
         while(_loc2_ < CCD_STAGE_NUM)
         {
            this.SetCursorOff(_loc2_);
            this.SetStagePanel(_loc2_);
            _loc2_++;
         }
         this.m_stageNum = 0;
         this.SetCursorOn(this.m_stageNum);
         this.m_keyHelp = new KeyHelpCode();
         if(this.m_keyHelp)
         {
            this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_UP,"MSG_Random");
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
            if(this.m_isNetworkMode == false && this.m_isBanCancel == false)
            {
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
            }
            this.m_keyHelp.PushKeyHelp();
            this.m_isPushKeyHelp = true;
         }
         this.m_isDisableRtbContents = false;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function SetBanCancel() : *
      {
         this.m_isBanCancel = true;
         if(this.m_keyHelp)
         {
            if(this.m_isPushKeyHelp == true)
            {
               this.m_keyHelp.PopKeyHelp();
            }
            this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_UP,"MSG_Random");
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
            this.m_keyHelp.PushKeyHelp();
            this.m_isPushKeyHelp = true;
         }
      }
      
      public function Update(param1:Event) : *
      {
         var _loc4_:Boolean = false;
         if(this.m_isNetworkMode && this.m_isClient)
         {
            return;
         }
         this.m_oldSelectY = this.m_selectY.GetSelValue();
         this.m_selectX.SelectMenuCtrl();
         this.m_selectY.SelectMenuCtrl();
         var _loc2_:int = this.m_selectX.GetSelValue();
         var _loc3_:int = this.m_selectY.GetSelValue();
         if(_loc3_ != CCD_STAGE_NUM_TBL_HEIGHT - 1)
         {
            this.m_selectX.SetMaxValue(CCD_STAGE_NUM_TBL_WIDTH - 1);
            if(this.m_oldSelectY == CCD_STAGE_NUM_TBL_HEIGHT - 1)
            {
               if(_loc2_ == 0)
               {
                  _loc2_ = CCD_STAGE_NUM_TBL_WIDTH_OFFSET;
               }
               else if(_loc2_ == 1)
               {
                  _loc2_ = CCD_STAGE_NUM_TBL_WIDTH / 2;
               }
               else
               {
                  _loc2_ = CCD_STAGE_NUM_TBL_WIDTH / 2 + 1;
               }
               this.m_selectX.SetSelValue(_loc2_);
            }
         }
         else if(this.m_oldSelectY == CCD_STAGE_NUM_TBL_HEIGHT - 2 || this.m_oldSelectY == 0)
         {
            this.m_selectX.SetMaxValue(CCD_STAGE_NUM_TBL_WIDTH_OFFSET - 1);
            if(_loc2_ < CCD_STAGE_SEL_WIDTH_OFFSET_LEFT)
            {
               _loc2_ = 0;
            }
            else if(_loc2_ < CCD_STAGE_SEL_WIDTH_OFFSET_CENTER)
            {
               _loc2_ = 1;
            }
            else
            {
               _loc2_ = CCD_STAGE_NUM_TBL_WIDTH_OFFSET - 1;
            }
            this.m_selectX.SetSelValue(_loc2_);
         }
         if(this.m_stageNum != this.m_stageNumTbl[_loc3_][_loc2_])
         {
            this.SetCursorOff(this.m_stageNum);
            this.m_stageNum = this.m_stageNumTbl[_loc3_][_loc2_];
            this.SetCursorOn(this.m_stageNum);
            this.SetStageNum(this.m_stageNum);
            ExternalInterface.call("RequestPlaySE_Select");
         }
         else if(this.m_inputPad.GetPadPress() == this.m_inputPad.GetKeyInputBtn_Ok())
         {
            _loc4_ = true;
            if(this.m_isInstall == true && this.m_stageNum != 0)
            {
               _loc4_ = false;
            }
            if(_loc4_)
            {
               this.SetCursorEnter(this.m_stageNum);
               this.SetDecide();
               removeEventListener(Event.ENTER_FRAME,this.Update);
               ExternalInterface.call("RequestPlaySE_Fix");
            }
            else
            {
               ExternalInterface.call("RequestPlaySE",18);
            }
         }
         else if(this.m_inputPad.GetPadPress() == this.m_inputPad.GetKeyInputBtn_Cancel())
         {
            if(this.m_isNetworkMode == false && this.m_isBanCancel == false)
            {
               this.SetCancel();
               removeEventListener(Event.ENTER_FRAME,this.Update);
               ExternalInterface.call("RequestPlaySE_Cancel");
            }
         }
         else if(this.m_inputPad.GetPadPress() == this.m_inputPad.GetKeyInputBtn_R_Up())
         {
            this.DecideRandom();
         }
      }
      
      public function DecideRandom() : *
      {
         this.m_randCount = 30;
         removeEventListener(Event.ENTER_FRAME,this.Update);
         addEventListener(Event.ENTER_FRAME,this.RandUpdate);
      }
      
      public function RandUpdate(param1:Event) : *
      {
         var _loc2_:Number = NaN;
         if(--this.m_randCount > 0)
         {
            this.SetCursorOff(this.m_stageNum);
            _loc2_ = CCD_STAGE_NUM;
            if(this.m_isDisableRtbContents == true)
            {
               _loc2_ = CCD_STAGE_NUM - CCD_STAGE_RTB_ADD_CONTENTS_NUM;
            }
            this.m_stageNum = Math.floor(Math.random() * _loc2_);
            this.SetCursorOn(this.m_stageNum);
            this.SetStageNum(this.m_stageNum);
            ExternalInterface.call("RequestPlaySE_Select");
         }
         else
         {
            if(this.m_isInstall)
            {
               this.SetCursorOff(this.m_stageNum);
               this.m_stageNum = 0;
               this.SetCursorOn(this.m_stageNum);
               this.SetStageNum(this.m_stageNum);
            }
            this.SetCursorEnter(this.m_stageNum);
            this.SetDecide();
            removeEventListener(Event.ENTER_FRAME,this.RandUpdate);
            ExternalInterface.call("RequestPlaySE_Fix");
         }
      }
      
      public function TimeOver() : *
      {
         this.SetCursorEnter(this.m_stageNum);
         this.SetStageNum(this.m_stageNum);
         this.SetDecide();
         removeEventListener(Event.ENTER_FRAME,this.Update);
         removeEventListener(Event.ENTER_FRAME,this.RandUpdate);
      }
      
      public function SetStagePanel(param1:Number) : *
      {
         this.GetStageImg(param1).all_images.gotoAndStop(param1 + 1);
      }
      
      public function SetCursorOff(param1:Number) : *
      {
         this.GetStageImg(param1).gotoAndStop("off");
      }
      
      public function SetCursorOn(param1:Number) : *
      {
         this.GetStageImg(param1).gotoAndStop("on");
      }
      
      public function SetCursorEnter(param1:Number) : *
      {
         this.GetStageImg(param1).gotoAndStop("enter");
      }
      
      public function SetSelectInfo(param1:int) : *
      {
         var _loc3_:int = 0;
         var _loc4_:Boolean = false;
         if(this.m_stageNum == param1)
         {
            return;
         }
         var _loc2_:int = 0;
         while(_loc2_ < CCD_STAGE_NUM_TBL_WIDTH)
         {
            _loc3_ = 0;
            _loc4_ = false;
            while(_loc3_ < CCD_STAGE_NUM_TBL_HEIGHT)
            {
               if(param1 == this.m_stageNumTbl[_loc3_][_loc2_])
               {
                  this.SetCursorOff(this.m_stageNum);
                  this.m_selectX.SetSelValue(_loc2_);
                  this.m_selectY.SetSelValue(_loc3_);
                  this.m_stageNum = param1;
                  this.SetCursorOn(this.m_stageNum);
                  this.SetStageNum(this.m_stageNum);
                  _loc4_ = true;
                  break;
               }
               _loc3_++;
            }
            if(_loc4_ == true)
            {
               break;
            }
            _loc2_++;
         }
      }
      
      public function SetDecideState() : *
      {
         this.SetCursorEnter(this.m_stageNum);
         this.SetDecide();
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function SetEnableClient() : *
      {
         this.m_isClient = true;
         this.PopKeyHelp();
      }
      
      private function GetStageImg(param1:Number) : MovieClip
      {
         var _loc2_:String = CCD_STAGE_IMAGE;
         if(param1 < 10)
         {
            _loc2_ += "0";
         }
         _loc2_ += param1.toString();
         return MovieClip(getChildByName(_loc2_));
      }
      
      public function PopKeyHelp() : *
      {
         if(this.m_keyHelp)
         {
            this.m_keyHelp.PopKeyHelp();
         }
      }
      
      public function SetInstallMode() : *
      {
         this.m_isInstall = true;
         var _loc1_:Number = 1;
         while(_loc1_ < CCD_STAGE_NUM)
         {
            this.GetStageImg(_loc1_).all_images.gotoAndStop("blank");
            _loc1_++;
         }
      }
      
      public function SetDisableRtbContents() : *
      {
         var _loc1_:Number = CCD_STAGE_NUM - CCD_STAGE_RTB_ADD_CONTENTS_NUM;
         while(_loc1_ < CCD_STAGE_NUM)
         {
            this.GetStageImg(_loc1_).all_images.gotoAndStop("blank");
            _loc1_++;
         }
         this.m_selectY.SetMaxValue(CCD_STAGE_NUM_TBL_HEIGHT - 2);
         this.m_isDisableRtbContents = true;
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

