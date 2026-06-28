package script.duel_boss
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol89")]
   public class nut_ia_stk2 extends base_ia
   {
      
      public var mc_btn:MovieClip;
      
      public var mc_eff_ok2:MovieClip;
      
      public var mc_tm:anm_tm_stk;
      
      public var mc_up:anm_up_stk;
      
      private const CCD_NO_ROLL_INTERVAL_FRAME:uint = 15;
      
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
      
      private var m_time:anm_tm_stk;
      
      private var m_gauge:anm_up_stk;
      
      private var m_isKeepCommand:Boolean;
      
      private var m_isInput:Boolean;
      
      private var m_tensionLevel:int;
      
      public function nut_ia_stk2()
      {
         super();
         addFrameScript(17,this.frame18,49,this.frame50,50,this.frame51,95,this.frame96,96,this.frame97,157,this.frame158,163,this.frame164,169,this.frame170,212,this.frame213);
         this.m_btn = MovieClip(getChildByName("mc_btn"));
         this.m_btnIcon = MovieClip(this.m_btn["mc_btn"]);
         this.m_time = anm_tm_stk(getChildByName("mc_tm"));
         this.m_gauge = anm_up_stk(getChildByName("mc_up"));
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
                  this.m_btnIcon.gotoAndStop(m_iaBtnTbl[param3]);
               }
               m_btnNo = param3;
            }
         }
         if(this.m_time == null)
         {
            this.m_time = anm_tm_stk(getChildByName("mc_tm"));
         }
         if(this.m_time)
         {
            this.m_time.SetTimeMax(param1);
         }
         this.SetTimeVisible(true);
         if(this.m_gauge == null)
         {
            this.m_gauge = anm_up_stk(getChildByName("mc_up"));
         }
         if(this.m_gauge)
         {
            this.m_gauge.SetGaugeMax(param2);
            this.m_gauge.SetSuccessVal(param4);
         }
         this.SetBtnGaugeVisible(true);
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
         }
         else if(m_gaugeParam.m_intervalFrame >= this.CCD_NO_ROLL_INTERVAL_FRAME)
         {
            this.m_isInput = false;
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
      
      internal function frame18() : *
      {
         this.stop();
      }
      
      internal function frame50() : *
      {
         this.stop();
      }
      
      internal function frame51() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame96() : *
      {
         this.stop();
      }
      
      internal function frame97() : *
      {
         gotoAndPlay("lv1");
      }
      
      internal function frame158() : *
      {
         this.stop();
      }
      
      internal function frame164() : *
      {
         gotoAndPlay("lv2");
      }
      
      internal function frame170() : *
      {
         this.stop();
      }
      
      internal function frame213() : *
      {
         this.stop();
      }
   }
}

