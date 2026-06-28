package script.duel_boss
{
   import InputPad.InputPadKeyCode;
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol47")]
   public class nut_ia extends base_ia
   {
      
      public var mc_cmd:MovieClip;
      
      public var mc_eff_ok0:anm_eff_ok1;
      
      public var mc_eff_ok1:MovieClip;
      
      public var mc_eff_ok2:MovieClip;
      
      public var mc_tm:nut_tm;
      
      private const CCD_LABEL_IN:String = "in";
      
      private const CCD_LABEL_LOOP:String = "loop";
      
      private const CCD_LABEL_OK:String = "ok";
      
      private const CCD_LABEL_NG:String = "ng";
      
      private var m_btnList:Array = new Array();
      
      private var m_btnIconList:Array = new Array();
      
      private var m_btnNoList:Array = new Array();
      
      private var m_btnIdx:int;
      
      private var m_time:nut_tm;
      
      private var m_eff_ok:MovieClip;
      
      private var m_isInput:Boolean;
      
      private var m_effectType:uint;
      
      private var m_inputList:Array = new Array();
      
      private var m_inputPad:InputPadKeyCode;
      
      private var m_isTwinStick:Boolean;
      
      public function nut_ia()
      {
         super();
         addFrameScript(16,this.frame17,38,this.frame39,62,this.frame63);
         var _loc1_:MovieClip = MovieClip(getChildByName("mc_cmd"));
         if(_loc1_)
         {
            this.m_btnList[0] = MovieClip(_loc1_.getChildByName("mc_btn5"));
            this.m_btnList[1] = MovieClip(_loc1_.getChildByName("mc_btn4"));
            this.m_btnList[2] = MovieClip(_loc1_.getChildByName("mc_btn3"));
            this.m_btnList[3] = MovieClip(_loc1_.getChildByName("mc_btn2"));
            this.m_btnList[4] = MovieClip(_loc1_.getChildByName("mc_btn1"));
         }
         var _loc2_:int = 0;
         while(_loc2_ < this.m_btnList.length)
         {
            this.m_btnList[_loc2_].visible = false;
            this.m_btnList[_loc2_].gotoAndStop("in");
            this.m_btnIconList[_loc2_] = MovieClip(this.m_btnList[_loc2_].getChildByName("mc_btn"));
            _loc2_++;
         }
         this.m_btnIdx = 0;
         this.m_time = nut_tm(getChildByName("mc_tm"));
         this.m_eff_ok = null;
         this.m_isInput = false;
         this.m_effectType = 0;
         this.m_inputPad = new InputPadKeyCode();
         this.m_inputPad.SetEnablePadOnly(this.m_inputPad.GetPad_1P());
         this.m_isTwinStick = false;
      }
      
      public function AllPlayAnm(param1:String) : *
      {
         this.gotoAndPlay(param1);
         if(this.m_time)
         {
            this.m_time.gotoAndPlay(param1);
         }
      }
      
      public function AddKey(param1:int, param2:int) : *
      {
         var _loc4_:String = null;
         var _loc3_:MovieClip = MovieClip(getChildByName("mc_cmd"));
         if(_loc3_)
         {
            if(this.m_btnIconList[param1])
            {
               if(param2 < m_iaBtnTbl.length && param2 >= 0)
               {
                  this.m_btnIconList[param1].gotoAndStop(m_iaBtnTbl[param2]);
                  if(this.m_btnIconList[param1].currentLabel == CCD_IA_BTN_R_STICK_RIGHT || this.m_btnIconList[param1].currentLabel == CCD_IA_BTN_R_STICK_LEFT || this.m_btnIconList[param1].currentLabel == CCD_IA_BTN_L_STICK_RIGHT || this.m_btnIconList[param1].currentLabel == CCD_IA_BTN_L_STICK_LEFT)
                  {
                     this.m_btnIconList[param1].play();
                     this.m_isTwinStick = true;
                  }
                  this.m_inputList[param1] = this.GetInputBtn(m_iaBtnTbl[param2]);
               }
               this.m_btnNoList[param1] = param2;
            }
            _loc4_ = "cmd" + this.m_btnNoList.length.toString();
            _loc3_.gotoAndStop(_loc4_);
            this.m_btnIdx = this.m_btnNoList.length - 1;
         }
      }
      
      override public function Initialize(param1:uint, param2:uint, param3:int, param4:uint, param5:Boolean, param6:Boolean, param7:uint) : *
      {
         RemoveUpdate();
         var _loc8_:MovieClip = MovieClip(getChildByName("mc_cmd"));
         if(_loc8_)
         {
            _loc8_.gotoAndStop("cmd1");
         }
         if(this.m_btnIconList[0])
         {
            if(param3 < m_iaBtnTbl.length && param3 >= 0)
            {
               this.m_btnIconList[0].gotoAndStop(m_iaBtnTbl[param3]);
               if(this.m_btnIconList[0].currentLabel == CCD_IA_BTN_R_STICK_RIGHT || this.m_btnIconList[0].currentLabel == CCD_IA_BTN_R_STICK_LEFT || this.m_btnIconList[0].currentLabel == CCD_IA_BTN_L_STICK_RIGHT || this.m_btnIconList[0].currentLabel == CCD_IA_BTN_L_STICK_LEFT)
               {
                  this.m_btnIconList[0].play();
               }
               this.m_inputList[0] = this.GetInputBtn(m_iaBtnTbl[param3]);
            }
            this.m_btnNoList[0] = param3;
         }
         if(this.m_time == null)
         {
            this.m_time = nut_tm(getChildByName("mc_tm"));
         }
         if(this.m_time)
         {
            this.m_time.SetTimeMax(param1);
         }
         this.SetTimeVisible(true);
         var _loc9_:MovieClip = MovieClip(getChildByName("mc_eff_ok0"));
         if(_loc9_)
         {
            _loc9_.visible = false;
         }
         var _loc10_:MovieClip = MovieClip(getChildByName("mc_eff_ok1"));
         if(_loc10_)
         {
            _loc10_.visible = false;
         }
         var _loc11_:MovieClip = MovieClip(getChildByName("mc_eff_ok2"));
         if(_loc11_)
         {
            _loc11_.visible = false;
         }
         if(this.m_eff_ok == null)
         {
            switch(param7)
            {
               case CCD_IA_EFF_NORMAL:
                  this.m_eff_ok = MovieClip(getChildByName("mc_eff_ok1"));
                  break;
               case CCD_IA_EFF_SPECIAL:
                  this.m_eff_ok = MovieClip(getChildByName("mc_eff_ok2"));
            }
         }
         SetEnableInput(false);
      }
      
      override public function Update(param1:Event) : *
      {
         var _loc2_:* = 0;
         var _loc3_:anm_eff_ok1 = null;
         if(m_gaugeParam == null)
         {
            return;
         }
         this.x = m_gaugeParam.m_posX;
         this.y = m_gaugeParam.m_posY;
         this.scaleX = m_gaugeParam.m_scaleX;
         this.scaleY = m_gaugeParam.m_scaleY;
         this.m_time.Update(m_gaugeParam.m_nowTime);
         if(this.m_time.IsTimeUp() == true)
         {
            FailedIa();
            this.AllPlayAnm(this.CCD_LABEL_NG);
            _loc2_ = this.m_btnIdx;
            while(_loc2_ >= 0)
            {
               if(this.m_btnList[_loc2_])
               {
                  this.m_btnList[_loc2_].gotoAndPlay(this.CCD_LABEL_NG);
               }
               if(this.m_btnIconList[_loc2_])
               {
                  this.m_btnIconList[_loc2_].gotoAndStop(m_failBtnTbl[this.m_btnNoList[_loc2_]]);
               }
               _loc2_--;
            }
            RemoveUpdate();
         }
         if(this.m_btnIdx > 0)
         {
            if(this.m_isTwinStick == false)
            {
               if(Boolean(this.m_inputList[this.m_btnIdx]) && Boolean(this.m_btnList[this.m_btnIdx]) && this.m_btnList[this.m_btnIdx].currentLabel == "loop")
               {
                  if(this.m_inputPad.GetPadPress() & this.m_inputList[this.m_btnIdx])
                  {
                     if(this.m_btnList[this.m_btnIdx])
                     {
                        this.m_btnList[this.m_btnIdx].gotoAndPlay(this.CCD_LABEL_OK);
                        _loc3_ = new anm_eff_ok1();
                        _loc3_.rotation += this.m_btnIdx * 45;
                        this.m_btnList[this.m_btnIdx].addChild(_loc3_);
                        PlaySuccessSE();
                     }
                     --this.m_btnIdx;
                  }
               }
            }
            else if(Boolean(this.m_inputList[0]) && Boolean(this.m_btnList[1]))
            {
               if(Boolean(this.m_inputPad.GetPadOn() & this.m_inputList[0]) && Boolean(this.m_inputPad.GetPadOn() & this.m_inputList[1]))
               {
                  SetEnableInput(true);
                  SuccessIa();
                  this.AllPlayAnm(this.CCD_LABEL_OK);
                  this.m_btnList[0].gotoAndPlay(this.CCD_LABEL_OK);
                  this.m_btnList[1].gotoAndPlay(this.CCD_LABEL_OK);
                  RemoveUpdate();
                  if(this.m_eff_ok)
                  {
                     this.m_eff_ok.visible = true;
                     this.m_eff_ok.gotoAndPlay(1);
                  }
               }
            }
         }
         else
         {
            SetEnableInput(true);
            if(m_gaugeParam.m_isInput == true)
            {
               SuccessIa();
               this.AllPlayAnm(this.CCD_LABEL_OK);
               if(this.m_btnList[0])
               {
                  this.m_btnList[0].gotoAndPlay(this.CCD_LABEL_OK);
               }
               RemoveUpdate();
               if(this.m_eff_ok)
               {
                  this.m_eff_ok.visible = true;
                  this.m_eff_ok.gotoAndPlay(1);
               }
            }
         }
         if(m_gaugeParam.m_isInput)
         {
            m_gaugeParam.m_isInput = false;
         }
      }
      
      override public function ReplayAnim() : *
      {
         this.AllPlayAnm(this.CCD_LABEL_IN);
         if(hasEventListener(Event.ENTER_FRAME) == false)
         {
            this.ProcBtnIn();
            addEventListener(Event.ENTER_FRAME,this.Update);
         }
      }
      
      override public function SetTimeVisible(param1:Boolean) : *
      {
         if(this.m_time)
         {
            this.m_time.visible = param1;
         }
      }
      
      public function GetInputBtn(param1:String) : uint
      {
         var _loc2_:uint = 0;
         trace("btnStr " + param1);
         if(param1 == CCD_IA_BTN_R_RIGHT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_R_Right();
         }
         else if(param1 == CCD_IA_BTN_R_DOWN)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_R_Down();
         }
         else if(param1 == CCD_IA_BTN_R_LEFT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_R_Left();
         }
         else if(param1 == CCD_IA_BTN_R_UP)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_R_Up();
         }
         else if(param1 == CCD_IA_BTN_L_1)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_L1();
         }
         else if(param1 == CCD_IA_BTN_L_2)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_L2();
         }
         else if(param1 == CCD_IA_BTN_R_1)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_R1();
         }
         else if(param1 == CCD_IA_BTN_R_2)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_R2();
         }
         else if(param1 == CCD_IA_BTN_KEY_UP)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_L_Up();
         }
         else if(param1 == CCD_IA_BTN_KEY_RIGHT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_L_Right();
         }
         else if(param1 == CCD_IA_BTN_KEY_DOWN)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_L_Down();
         }
         else if(param1 == CCD_IA_BTN_KEY_LEFT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_L_Left();
         }
         else if(param1 == CCD_IA_BTN_R_STICK_LOOP)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_R3();
         }
         else if(param1 == CCD_IA_BTN_L_STICK_LOOP)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_L3();
         }
         else if(param1 == CCD_IA_BTN_R_STICK_RIGHT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_RS_Right();
         }
         else if(param1 == CCD_IA_BTN_R_STICK_DOWN)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_RS_Down();
         }
         else if(param1 == CCD_IA_BTN_R_STICK_LEFT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_RS_Left();
         }
         else if(param1 == CCD_IA_BTN_R_STICK_UP)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_RS_Up();
         }
         else if(param1 == CCD_IA_BTN_L_STICK_RIGHT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_LS_Right();
         }
         else if(param1 == CCD_IA_BTN_L_STICK_DOWN)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_LS_Down();
         }
         else if(param1 == CCD_IA_BTN_L_STICK_LEFT)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_LS_Left();
         }
         else if(param1 == CCD_IA_BTN_L_STICK_UP)
         {
            _loc2_ = this.m_inputPad.GetKeyInputBtn_LS_Up();
         }
         return _loc2_;
      }
      
      public function ProcBtnIn() : *
      {
         var _loc1_:int = this.m_btnNoList.length - 1;
         if(this.m_btnList[_loc1_])
         {
            this.m_btnList[_loc1_].visible = true;
            this.m_btnList[_loc1_].gotoAndPlay(this.CCD_LABEL_IN);
         }
         addEventListener(Event.ENTER_FRAME,this.UpdateBtnIn);
      }
      
      public function UpdateBtnIn(param1:Event) : *
      {
         var _loc2_:* = int(this.m_btnNoList.length - 1);
         while(_loc2_ > 0)
         {
            if(Boolean(this.m_btnList[_loc2_]) && this.m_btnList[_loc2_].currentLabel == "next")
            {
               if(Boolean(this.m_btnList[_loc2_ - 1]) && this.m_btnList[_loc2_ - 1].visible == false)
               {
                  this.m_btnList[_loc2_ - 1].visible = true;
                  this.m_btnList[_loc2_ - 1].gotoAndPlay("in");
               }
            }
            _loc2_--;
         }
         if(Boolean(this.m_btnList[0]) && this.m_btnList[0].currentLabel == "loop")
         {
            removeEventListener(Event.ENTER_FRAME,this.UpdateBtnIn);
         }
      }
      
      internal function frame17() : *
      {
         this.stop();
      }
      
      internal function frame39() : *
      {
         this.stop();
      }
      
      internal function frame63() : *
      {
         this.stop();
      }
   }
}

