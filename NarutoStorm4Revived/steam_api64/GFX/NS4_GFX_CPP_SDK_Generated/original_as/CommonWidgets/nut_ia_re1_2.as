package script.duel_boss
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol69")]
   public class nut_ia_re1 extends base_ia
   {
      
      public var mc_btn:MovieClip;
      
      public var mc_eff_re:MovieClip;
      
      public var mc_tm:anm_tm_re;
      
      public var mc_up:anm_up_re;
      
      private const CCD_NO_PRESS_INTERVAL_FRAME:uint = 9;
      
      private const CCD_IA_BTN_R_RIGHT_RE:String = "btn_1_loop";
      
      private const CCD_IA_BTN_R_DOWN_RE:String = "btn_2_loop";
      
      private const CCD_IA_BTN_R_LEFT_RE:String = "btn_3_loop";
      
      private const CCD_IA_BTN_R_UP_RE:String = "btn_4_loop";
      
      private const CCD_LABEL_LOOP:String = "loop";
      
      private const CCD_LABEL_LEVEL0_1:String = "lv1";
      
      private const CCD_LABEL_LEVEL1_0:String = "back_loop";
      
      private const CCD_LABEL_LEVEL1_2:String = "lv2";
      
      private const CCD_LABEL_LEVEL2_1:String = "back_lv1";
      
      private const CCD_LABEL_LEVEL2_3:String = "lv3";
      
      private const CCD_LABEL_LEVEL3_2:String = "back_lv2";
      
      private const CCD_LABEL_NG:String = "ng";
      
      private const CCD_LABEL_OK:String = "ok";
      
      private const CCD_LABEL_SF_GET:String = "sf_get";
      
      private const CCD_LABEL_END:String = "end";
      
      private var m_btn:MovieClip;
      
      private var m_btnIcon:MovieClip;
      
      private var m_time:anm_tm_re;
      
      private var m_gauge:anm_up_re;
      
      private var m_eff_re:MovieClip;
      
      private var m_isKeepCommand:Boolean;
      
      private var m_isInput:Boolean;
      
      private var m_tensionLevel:int;
      
      public function nut_ia_re1()
      {
         super();
         addFrameScript(9,this.frame10,40,this.frame41,41,this.frame42,58,this.frame59,59,this.frame60,85,this.frame86,86,this.frame87,90,this.frame91,124,this.frame125);
         this.m_btn = MovieClip(getChildByName("mc_btn"));
         this.m_btnIcon = MovieClip(this.m_btn["mc_btn"]);
         this.m_time = anm_tm_re(getChildByName("mc_tm"));
         this.m_gauge = anm_up_re(getChildByName("mc_up"));
         this.m_eff_re = MovieClip(getChildByName("mc_eff_re"));
         this.m_isKeepCommand = false;
         this.m_isInput = false;
         this.m_tensionLevel = 0;
      }
      
      public function AllPlayAnm(param1:String) : *
      {
         this.gotoAndPlay(param1);
         if(this.m_btn)
         {
            this.m_btn.gotoAndPlay(param1);
         }
         if(this.m_time)
         {
            this.m_time.gotoAndPlay(param1);
         }
         if(this.m_gauge)
         {
            this.m_gauge.gotoAndPlay(param1);
         }
      }
      
      override public function Initialize(param1:uint, param2:uint, param3:int, param4:uint, param5:Boolean, param6:Boolean, param7:uint) : *
      {
         RemoveUpdate();
         if(this.m_btn == null)
         {
            this.m_btn = MovieClip(getChildByName("mc_btn"));
         }
         if(this.m_btn)
         {
            if(this.m_btnIcon)
            {
               if(param3 < m_iaBtnTbl.length && param3 >= 0)
               {
                  if(m_iaBtnTbl[param3] == CCD_IA_BTN_R_RIGHT)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_RIGHT_RE);
                  }
                  else if(m_iaBtnTbl[param3] == CCD_IA_BTN_R_DOWN)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_DOWN_RE);
                  }
                  else if(m_iaBtnTbl[param3] == CCD_IA_BTN_R_LEFT)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_LEFT_RE);
                  }
                  else if(m_iaBtnTbl[param3] == CCD_IA_BTN_R_UP)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_UP_RE);
                  }
                  else
                  {
                     this.m_btnIcon.gotoAndStop(m_iaBtnTbl[param3]);
                  }
                  m_btnNo = param3;
               }
            }
         }
         if(this.m_time == null)
         {
            this.m_time = anm_tm_re(getChildByName("mc_tm"));
         }
         if(this.m_time)
         {
            this.m_time.SetTimeMax(param1);
         }
         this.SetTimeVisible(true);
         if(this.m_gauge == null)
         {
            this.m_gauge = anm_up_re(getChildByName("mc_up"));
         }
         if(this.m_gauge)
         {
            this.m_gauge.SetGaugeMax(param2);
            this.m_gauge.SetSuccessVal(param4);
         }
         this.SetBtnGaugeVisible(true);
         if(this.m_eff_re == null)
         {
            this.m_eff_re = MovieClip(getChildByName("mc_eff_re"));
         }
         if(this.m_eff_re)
         {
            this.m_eff_re.visible = false;
            this.m_eff_re.stop();
         }
         this.AllPlayAnm("in");
         this.m_isKeepCommand = param6;
         this.m_tensionLevel = 0;
      }
      
      override public function Update(param1:Event) : *
      {
         if(m_gaugeParam == null)
         {
            return;
         }
         this.x = m_gaugeParam.m_posX;
         this.y = m_gaugeParam.m_posY;
         this.scaleX = m_gaugeParam.m_scaleX;
         this.scaleY = m_gaugeParam.m_scaleY;
         this.ProcTension();
         if(m_gaugeParam.m_isInput == true)
         {
            this.m_isInput = true;
            if(this.m_btnIcon)
            {
               this.m_btnIcon.gotoAndStop(m_hldBtnTbl[m_btnNo]);
            }
            if(this.m_eff_re)
            {
               this.m_eff_re.visible = true;
               this.m_eff_re.gotoAndPlay(1);
            }
         }
         else
         {
            if(m_gaugeParam.m_intervalFrame >= this.CCD_NO_PRESS_INTERVAL_FRAME)
            {
               this.m_isInput = false;
            }
            if(this.m_btnIcon)
            {
               if(m_iaBtnTbl[m_btnNo] == CCD_IA_BTN_R_RIGHT)
               {
                  if(this.m_btnIcon.currentLabel != this.CCD_IA_BTN_R_RIGHT_RE)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_RIGHT_RE);
                  }
               }
               else if(m_iaBtnTbl[m_btnNo] == CCD_IA_BTN_R_DOWN)
               {
                  if(this.m_btnIcon.currentLabel != this.CCD_IA_BTN_R_DOWN_RE)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_DOWN_RE);
                  }
               }
               else if(m_iaBtnTbl[m_btnNo] == CCD_IA_BTN_R_LEFT)
               {
                  if(this.m_btnIcon.currentLabel != this.CCD_IA_BTN_R_LEFT_RE)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_LEFT_RE);
                  }
               }
               else if(m_iaBtnTbl[m_btnNo] == CCD_IA_BTN_R_UP)
               {
                  if(this.m_btnIcon.currentLabel != this.CCD_IA_BTN_R_UP_RE)
                  {
                     this.m_btnIcon.gotoAndPlay(this.CCD_IA_BTN_R_UP_RE);
                  }
               }
               else
               {
                  this.m_btnIcon.gotoAndStop(m_iaBtnTbl[m_btnNo]);
               }
            }
         }
         this.m_time.Update(m_gaugeParam.m_nowTime);
         if(this.m_time.IsTimeUp() == false)
         {
            this.m_gauge.Update(m_gaugeParam.m_nowGauge);
            if(this.m_gauge.IsSuccess() == true)
            {
               if(this.m_isKeepCommand != true)
               {
                  SuccessIa();
                  this.AllPlayAnm(this.CCD_LABEL_OK);
                  if(this.m_eff_re)
                  {
                     this.m_eff_re.visible = false;
                     this.m_eff_re.stop();
                  }
                  RemoveUpdate();
               }
            }
         }
         else
         {
            if(this.m_gauge.IsSuccess() == true && this.m_isKeepCommand == true)
            {
               SuccessIa();
               this.AllPlayAnm(this.CCD_LABEL_OK);
            }
            else
            {
               FailedIa();
               this.AllPlayAnm(this.CCD_LABEL_NG);
               if(this.m_btnIcon)
               {
                  this.m_btnIcon.gotoAndStop(m_failBtnTbl[m_btnNo]);
               }
            }
            if(this.m_eff_re)
            {
               this.m_eff_re.visible = false;
               this.m_eff_re.stop();
            }
            RemoveUpdate();
         }
         if(m_gaugeParam.m_isInput)
         {
            m_gaugeParam.m_isInput = false;
         }
      }
      
      public function ProcTension() : *
      {
         var _loc1_:int = 0;
         var _loc2_:String = null;
         if(this.m_gauge)
         {
            _loc1_ = this.m_gauge.GetTensionLevel();
            if(this.m_tensionLevel != _loc1_)
            {
               this.m_tensionLevel = _loc1_;
               _loc2_ = "";
               if(this.m_tensionLevel == 0)
               {
                  _loc2_ = "loop";
               }
               else if(this.m_tensionLevel == 1)
               {
                  _loc2_ = "lv1";
               }
               else if(this.m_tensionLevel == 2)
               {
                  _loc2_ = "lv2";
               }
               else if(this.m_tensionLevel == 3)
               {
                  _loc2_ = "lv3";
               }
               this.gotoAndPlay(_loc2_);
               if(this.m_time)
               {
                  this.m_time.gotoAndPlay(_loc2_);
               }
               if(this.m_gauge)
               {
                  this.m_gauge.gotoAndPlay(_loc2_);
               }
            }
         }
      }
      
      override public function ReplayAnim() : *
      {
         this.AllPlayAnm("in");
         if(hasEventListener(Event.ENTER_FRAME) == false)
         {
            addEventListener(Event.ENTER_FRAME,this.Update);
         }
         if(this.m_btnIcon == null)
         {
            this.m_btnIcon = MovieClip(getChildByName("mc_btn.mc_btn"));
         }
         if(this.m_btnIcon)
         {
            this.m_btnIcon.gotoAndStop(m_iaBtnTbl[m_btnNo]);
         }
      }
      
      override public function SetTimeVisible(param1:Boolean) : *
      {
         if(this.m_time)
         {
            this.m_time.visible = param1;
         }
      }
      
      override public function SetBtnGaugeVisible(param1:Boolean) : *
      {
         if(this.m_gauge)
         {
            this.m_gauge.visible = param1;
         }
      }
      
      internal function frame10() : *
      {
         this.stop();
      }
      
      internal function frame41() : *
      {
         this.stop();
      }
      
      internal function frame42() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame59() : *
      {
         this.stop();
      }
      
      internal function frame60() : *
      {
         gotoAndPlay("lv1");
      }
      
      internal function frame86() : *
      {
         this.stop();
      }
      
      internal function frame87() : *
      {
         gotoAndPlay("lv2");
      }
      
      internal function frame91() : *
      {
         this.stop();
      }
      
      internal function frame125() : *
      {
         this.stop();
      }
   }
}

