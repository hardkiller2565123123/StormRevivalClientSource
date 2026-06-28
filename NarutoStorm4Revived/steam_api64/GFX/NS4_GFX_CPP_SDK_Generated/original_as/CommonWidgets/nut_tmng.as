package script.duel_boss
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.*;
   import script.d_boss_plat.nut_btn;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol99")]
   public class nut_tmng extends base_ia
   {
      
      public var mc_btn:nut_btn;
      
      public var mc_eff_ok1:MovieClip;
      
      public var mc_eff_ok2:MovieClip;
      
      public var mc_tmng:MovieClip;
      
      private const CCD_LABEL_LOOP:String = "loop";
      
      private const CCD_LABEL_NG:String = "ng";
      
      private const CCD_LABEL_NG_END:String = "ng_end";
      
      private const CCD_LABEL_OK:String = "ok";
      
      private const CCD_LABEL_OK_END:String = "ok_end";
      
      private const CCD_LABEL_JUST:String = "just";
      
      private const CCD_LABEL_JUST_END:String = "just_end";
      
      private const CCD_JUST_FRAME_START:int = 60;
      
      private const CCD_JUST_FRAME_END:int = 69;
      
      private const CCD_OK_DEF_FRAME:int = 4;
      
      private var m_btn:MovieClip;
      
      private var m_tmng:MovieClip;
      
      private var m_isCountUp:Boolean;
      
      private var m_tmngCount:int;
      
      private var m_tmngFrameRate:Number;
      
      private var m_okArea:int;
      
      public function nut_tmng()
      {
         super();
         addFrameScript(29,this.frame30,47,this.frame48,63,this.frame64,94,this.frame95);
         this.m_tmng = MovieClip(getChildByName("mc_tmng"));
      }
      
      override public function Initialize(param1:uint, param2:uint, param3:int, param4:uint, param5:Boolean, param6:Boolean, param7:uint) : *
      {
         RemoveUpdate();
         gotoAndStop("in");
         if(this.m_btn == null)
         {
            this.m_btn = MovieClip(getChildByName("mc_btn"));
         }
         if(param3 < m_iaBtnTbl.length && param3 >= 0)
         {
            this.m_btn.gotoAndStop(m_iaBtnTbl[param3]);
            m_btnNo = param3;
         }
         this.m_isCountUp = false;
         this.m_tmngCount = 0;
         this.m_tmngFrameRate = 1;
         this.m_okArea = this.CCD_OK_DEF_FRAME;
         this.SetTmngAnmFrame(param1);
         SetEnableInput(false);
      }
      
      override public function Update(param1:Event) : *
      {
         var _loc2_:int = 0;
         var _loc3_:String = null;
         var _loc4_:String = null;
         if(m_gaugeParam == null)
         {
            return;
         }
         if(this.m_isCountUp)
         {
            ++this.m_tmngCount;
            _loc2_ = this.m_tmngCount * this.m_tmngFrameRate;
            if(_loc2_ > this.m_tmng.totalFrames)
            {
               _loc2_ = this.m_tmng.totalFrames;
               this.m_isCountUp = false;
            }
            this.m_tmng.gotoAndStop(_loc2_);
         }
         x = m_gaugeParam.m_posX;
         y = m_gaugeParam.m_posY;
         scaleX = m_gaugeParam.m_scaleX;
         scaleY = m_gaugeParam.m_scaleY;
         if(this.m_tmng.currentLabel != "in")
         {
            SetEnableInput(true);
            _loc3_ = "";
            if(m_gaugeParam.m_isInput == true)
            {
               _loc3_ = this.JudgeTiming();
               RemoveUpdate();
               this.m_isCountUp = false;
            }
            else if(this.m_tmng.currentLabel == "end")
            {
               _loc3_ = this.CCD_LABEL_NG;
               RemoveUpdate();
            }
            if(_loc3_ != "")
            {
               _loc4_ = this.m_btn.currentLabel;
               if(_loc3_ == this.CCD_LABEL_JUST)
               {
                  GreatSuccessIa();
               }
               else if(_loc3_ == this.CCD_LABEL_OK)
               {
                  SuccessIa();
               }
               else if(_loc3_ == this.CCD_LABEL_NG)
               {
                  FailedIa();
                  this.m_btn.gotoAndStop(m_failBtnTbl[m_btnNo]);
               }
               this.m_btn = null;
               this.m_tmng = null;
               gotoAndPlay(_loc3_);
            }
         }
         if(m_gaugeParam.m_isInput)
         {
            m_gaugeParam.m_isInput = false;
         }
      }
      
      override public function ReplayAnim() : *
      {
         this.gotoAndPlay("in");
         if(hasEventListener(Event.ENTER_FRAME) == false)
         {
            addEventListener(Event.ENTER_FRAME,this.Update);
         }
         if(this.m_btn == null)
         {
            this.m_btn = MovieClip(getChildByName("mc_btn"));
         }
         if(this.m_btn)
         {
            this.m_btn.gotoAndStop(m_iaBtnTbl[m_btnNo]);
         }
         if(this.m_tmng == null)
         {
            this.m_tmng = MovieClip(getChildByName("mc_tmng"));
         }
         this.m_isCountUp = true;
      }
      
      private function JudgeTiming() : String
      {
         var _loc1_:String = "";
         var _loc2_:int = this.m_tmng.currentFrame;
         if(_loc2_ >= this.CCD_JUST_FRAME_START && _loc2_ <= this.CCD_JUST_FRAME_END)
         {
            _loc1_ = this.CCD_LABEL_JUST;
         }
         else if(_loc2_ >= this.CCD_JUST_FRAME_START - this.m_okArea && _loc2_ <= this.CCD_JUST_FRAME_END + this.m_okArea)
         {
            _loc1_ = this.CCD_LABEL_OK;
         }
         else
         {
            _loc1_ = this.CCD_LABEL_NG;
         }
         return _loc1_;
      }
      
      private function SetTmngAnmFrame(param1:int) : *
      {
         this.m_tmngFrameRate = this.m_tmng.totalFrames / param1;
      }
      
      public function SetOkFrame(param1:int) : *
      {
         this.m_okArea = param1;
      }
      
      internal function frame30() : *
      {
         this.stop();
      }
      
      internal function frame48() : *
      {
         this.stop();
      }
      
      internal function frame64() : *
      {
         this.stop();
      }
      
      internal function frame95() : *
      {
         this.stop();
      }
   }
}

