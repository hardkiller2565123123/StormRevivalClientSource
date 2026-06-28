package script.gauge_b
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.utils.Dictionary;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol26")]
   public class nut_b_life extends MovieClip
   {
      
      private static const CCD_GAUGE_MAX:* = 4;
      
      private static const CCD_STAY_NUM:* = 3;
      
      private static const CCD_MIN_SUB:* = 0.0001;
      
      public static const DELAY_GAUGE_SPEED_RATE:* = 0.2;
      
      public static const ONE_GAUGE_VOLUME:* = 0.25;
      
      public static const DAMAGE_GAUGE_VISIBLE_FRAME:* = 4;
      
      public static const STAY_1:* = 0;
      
      public static const STAY_2:* = 1;
      
      public static const STAY_3:* = 2;
      
      public static const GAUGE_1:* = 0;
      
      public static const GAUGE_2:* = 1;
      
      public static const GAUGE_3:* = 2;
      
      public static const GAUGE_4:* = 3;
      
      public var mc_l_bar1:MovieClip;
      
      public var mc_l_eff:MovieClip;
      
      public var mc_stay1:MovieClip;
      
      public var mc_stay2:MovieClip;
      
      public var mc_stay3:MovieClip;
      
      private var m_life_eff:MovieClip;
      
      private var m_life_bar:MovieClip;
      
      private var m_stay:Array;
      
      public var m_nowLifeRate:Number;
      
      public var m_delayLifeRate:Number;
      
      public var m_comboCounter:Number;
      
      public var m_lifeGaugeBaseX:Number;
      
      public var m_isDirectDamage:Boolean;
      
      public var m_nowLifeGaugeIdx:int;
      
      public var m_delayLifeGaugeIdx:int;
      
      private var m_gaugeNum:uint = 0;
      
      private var m_lifeColMap:Dictionary;
      
      public function nut_b_life()
      {
         var _loc2_:* = undefined;
         var _loc3_:int = 0;
         var _loc4_:MovieClip = null;
         this.m_stay = new Array();
         this.m_lifeColMap = new Dictionary();
         super();
         addFrameScript(0,this.frame1,1,this.frame2,18,this.frame19,26,this.frame27,27,this.frame28,44,this.frame45,52,this.frame53,53,this.frame54,70,this.frame71,78,this.frame79,79,this.frame80,87,this.frame88);
         this.cacheAsBitmap = true;
         this.m_life_eff = MovieClip(getChildByName("mc_l_eff"));
         this.m_life_bar = MovieClip(getChildByName("mc_l_bar1"));
         this.m_life_bar.cacheAsBitmap = true;
         var _loc1_:int = 0;
         while(_loc1_ < CCD_GAUGE_MAX)
         {
            _loc2_ = false;
            if(_loc1_ == GAUGE_1)
            {
               _loc2_ = true;
            }
            MovieClip(this.m_life_bar.getChildByName("mc_l_bar" + Number(_loc1_ + 1).toString())).visible = _loc2_;
            MovieClip(this.m_life_bar.getChildByName("mc_ld_bar" + Number(_loc1_ + 1).toString())).visible = _loc2_;
            _loc1_++;
         }
         this.m_stay.length = 0;
         this.m_stay.push(MovieClip(getChildByName("mc_stay1")));
         this.m_stay.push(MovieClip(getChildByName("mc_stay2")));
         this.m_stay.push(MovieClip(getChildByName("mc_stay3")));
         _loc1_ = 0;
         while(_loc1_ < this.m_stay.length)
         {
            this.m_stay[_loc1_].cacheAsBitmap = true;
            _loc3_ = 0;
            while(_loc3_ < CCD_STAY_NUM)
            {
               _loc4_ = MovieClip(this.m_stay[_loc1_].getChildByName("mc_bar" + Number(_loc3_ + 1).toString()));
               _loc2_ = false;
               if(_loc3_ == _loc1_)
               {
                  _loc2_ = true;
               }
               _loc4_.visible = _loc2_;
               _loc3_++;
            }
            _loc1_++;
         }
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      public function OnRemove(param1:Event) : *
      {
         trace("OnRemove!!");
         if(hasEventListener(Event.ENTER_FRAME) == true)
         {
            removeEventListener(Event.ENTER_FRAME,this.Update);
         }
         if(hasEventListener(Event.REMOVED_FROM_STAGE) == true)
         {
            removeEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
         }
      }
      
      public function Initialize() : *
      {
         this.m_nowLifeRate = 1;
         this.m_delayLifeRate = 1;
         this.m_comboCounter = 0;
         this.m_lifeGaugeBaseX = this.m_life_bar.mc_l_bar1.x;
         this.m_isDirectDamage = false;
         this.m_nowLifeGaugeIdx = 1;
         this.m_delayLifeGaugeIdx = 0;
         this.UseLifeGauge_4();
         this.gotoAndStop("lif1");
         this.m_life_eff.mc_l_eff.alpha = 0;
         if(hasEventListener(Event.ENTER_FRAME) == false)
         {
            addEventListener(Event.ENTER_FRAME,this.Update);
         }
      }
      
      public function Finalize() : *
      {
         if(hasEventListener(Event.ENTER_FRAME) == true)
         {
            removeEventListener(Event.ENTER_FRAME,this.Update);
         }
      }
      
      public function Update(param1:Event) : *
      {
         var _loc7_:Number = NaN;
         if(this.m_comboCounter <= 0)
         {
            if(this.m_delayLifeRate != this.m_nowLifeRate)
            {
               this.m_delayLifeRate += (this.m_nowLifeRate - this.m_delayLifeRate) * DELAY_GAUGE_SPEED_RATE;
               if(Math.abs(this.m_nowLifeRate - this.m_delayLifeRate) <= CCD_MIN_SUB)
               {
                  this.m_delayLifeRate = this.m_nowLifeRate;
               }
            }
         }
         var _loc2_:int = this.m_nowLifeGaugeIdx;
         var _loc3_:MovieClip = null;
         _loc3_ = this.GetCurrentLifeGauge();
         var _loc4_:Number = this.GetGaugeFrameRate(this.m_nowLifeRate);
         _loc3_.x = this.m_lifeGaugeBaseX - _loc4_ * _loc3_.width + _loc3_.width;
         this.m_life_eff.mc_l_eff.x = _loc3_.x;
         if(_loc2_ != this.m_nowLifeGaugeIdx)
         {
            if(_loc2_ < this.m_nowLifeGaugeIdx)
            {
               _loc7_ = this.m_nowLifeGaugeIdx - 1;
               if(_loc7_ != 0)
               {
                  this.gotoAndPlay("lif" + _loc7_.toString() + "_out");
                  trace("lif" + _loc2_.toString() + "_out");
               }
            }
            else
            {
               this.gotoAndStop("lif" + this.m_nowLifeGaugeIdx.toString());
               trace("lif" + this.m_nowLifeGaugeIdx.toString());
            }
            this.m_delayLifeRate = this.m_nowLifeRate;
         }
         else if(this.m_nowLifeGaugeIdx == DAMAGE_GAUGE_VISIBLE_FRAME && this.m_nowLifeRate < CCD_MIN_SUB)
         {
            this.gotoAndPlay("lif4_out");
            this.m_delayLifeRate = this.m_nowLifeRate;
            this.Finalize();
         }
         var _loc5_:MovieClip = null;
         _loc5_ = this.GetCurrentDelayGauge();
         var _loc6_:Number = this.GetGaugeFrameRate(this.m_delayLifeRate);
         _loc5_.x = this.m_lifeGaugeBaseX - _loc6_ * _loc5_.width + _loc5_.width;
         if(this.m_life_eff.mc_l_eff.alpha > 0)
         {
            this.m_life_eff.mc_l_eff.alpha -= 0.05;
         }
      }
      
      private function GetCurrentLifeGauge() : MovieClip
      {
         var _loc5_:MovieClip = null;
         var _loc6_:Number = NaN;
         var _loc1_:Number = 1 / Number(this.m_gaugeNum);
         var _loc2_:int = 0;
         var _loc3_:MovieClip = null;
         var _loc4_:Boolean = false;
         while(_loc2_ < CCD_GAUGE_MAX)
         {
            _loc5_ = MovieClip(this.m_life_bar.getChildByName("mc_l_bar" + Number(_loc2_ + 1).toString()));
            _loc5_.visible = false;
            if(_loc2_ < this.m_gaugeNum)
            {
               _loc6_ = this.m_gaugeNum - 1 - _loc2_;
               if(_loc4_ == false && this.m_nowLifeRate >= _loc1_ * _loc6_)
               {
                  this.m_nowLifeGaugeIdx = _loc2_ + 1;
                  _loc4_ = true;
               }
            }
            if(_loc2_ + 1 == this.m_lifeColMap[this.m_nowLifeGaugeIdx])
            {
               _loc5_.visible = true;
               _loc3_ = _loc5_;
            }
            _loc2_++;
         }
         return _loc3_;
      }
      
      private function GetCurrentDelayGauge() : MovieClip
      {
         var _loc5_:MovieClip = null;
         var _loc6_:Number = NaN;
         var _loc1_:Number = 1 / Number(this.m_gaugeNum);
         var _loc2_:int = 0;
         var _loc3_:MovieClip = null;
         var _loc4_:Boolean = false;
         while(_loc2_ < CCD_GAUGE_MAX)
         {
            _loc5_ = MovieClip(this.m_life_bar.getChildByName("mc_ld_bar" + Number(_loc2_ + 1).toString()));
            _loc5_.visible = false;
            if(_loc2_ < this.m_gaugeNum)
            {
               _loc6_ = this.m_gaugeNum - 1 - _loc2_;
               if(_loc4_ == false && this.m_delayLifeRate >= _loc1_ * _loc6_)
               {
                  this.m_delayLifeGaugeIdx = _loc2_ + 1;
                  _loc4_ = true;
               }
            }
            if(_loc2_ + 1 == this.m_lifeColMap[this.m_delayLifeGaugeIdx])
            {
               _loc5_.visible = true;
               _loc3_ = _loc5_;
            }
            _loc2_++;
         }
         return _loc3_;
      }
      
      private function GetGaugeFrameRate(param1:Number) : Number
      {
         var _loc2_:Number = 1 / this.m_gaugeNum;
         var _loc3_:* = int(this.m_gaugeNum - 1);
         while(_loc3_ >= 0)
         {
            if(param1 >= _loc2_ * _loc3_)
            {
               param1 = (param1 - _loc2_ * _loc3_) * this.m_gaugeNum;
               break;
            }
            _loc3_--;
         }
         return param1;
      }
      
      public function SetLifeRate(param1:Number) : *
      {
         if(this.m_isDirectDamage)
         {
            if(this.m_nowLifeRate > param1)
            {
               this.m_life_eff.mc_l_eff.alpha = 1;
               this.m_isDirectDamage = false;
            }
         }
         this.m_nowLifeRate = param1;
      }
      
      public function SetLifeRateNonDelay(param1:Number) : *
      {
         this.m_nowLifeRate = param1;
         this.m_delayLifeRate = param1;
         this.GetCurrentLifeGauge();
         this.gotoAndStop("lif" + this.m_nowLifeGaugeIdx.toString());
         trace("lif" + this.m_nowLifeGaugeIdx.toString());
      }
      
      public function SetComboCount(param1:Number) : *
      {
         if(this.m_comboCounter < param1)
         {
            this.m_isDirectDamage = true;
         }
         this.m_comboCounter = param1;
      }
      
      public function UseLifeGauge_4() : *
      {
         var _loc2_:int = 0;
         var _loc3_:Boolean = false;
         var _loc1_:uint = 0;
         while(_loc1_ < this.m_stay.length)
         {
            this.m_stay[_loc1_].visible = true;
            _loc2_ = 0;
            while(_loc2_ < CCD_STAY_NUM)
            {
               _loc3_ = false;
               if(_loc2_ == _loc1_)
               {
                  _loc3_ = true;
               }
               MovieClip(this.m_stay[_loc1_].getChildByName("mc_bar" + Number(_loc2_ + 1).toString())).visible = _loc3_;
               _loc2_++;
            }
            _loc1_++;
         }
         this.m_gaugeNum = 4;
         if(this.m_lifeColMap != null)
         {
            this.m_lifeColMap = null;
            this.m_lifeColMap = new Dictionary();
         }
         this.m_lifeColMap[1] = 1;
         this.m_lifeColMap[2] = 2;
         this.m_lifeColMap[3] = 3;
         this.m_lifeColMap[4] = 4;
      }
      
      public function UseLifeGauge_3() : *
      {
         var _loc4_:int = 0;
         var _loc5_:MovieClip = null;
         var _loc1_:uint = 0;
         while(_loc1_ < this.m_stay.length)
         {
            if(_loc1_ == STAY_3)
            {
               this.m_stay[_loc1_].visible = false;
            }
            else
            {
               this.m_stay[_loc1_].visible = true;
            }
            _loc4_ = 0;
            while(_loc4_ < CCD_STAY_NUM)
            {
               _loc5_ = MovieClip(this.m_stay[_loc1_].getChildByName("mc_bar" + Number(_loc4_ + 1).toString()));
               if(_loc5_)
               {
                  _loc5_.visible = false;
               }
               _loc4_++;
            }
            _loc1_++;
         }
         this.m_gaugeNum = 3;
         var _loc2_:MovieClip = MovieClip(this.m_stay[STAY_1].getChildByName("mc_bar1"));
         if(_loc2_)
         {
            _loc2_.visible = true;
         }
         var _loc3_:MovieClip = MovieClip(this.m_stay[STAY_2].getChildByName("mc_bar3"));
         if(_loc3_)
         {
            _loc3_.visible = true;
         }
         if(this.m_lifeColMap != null)
         {
            this.m_lifeColMap = null;
            this.m_lifeColMap = new Dictionary();
         }
         this.m_lifeColMap[1] = 1;
         this.m_lifeColMap[2] = 2;
         this.m_lifeColMap[3] = 3;
      }
      
      public function UseLifeGauge_2() : *
      {
         var _loc3_:int = 0;
         var _loc4_:MovieClip = null;
         var _loc1_:uint = 0;
         while(_loc1_ < this.m_stay.length)
         {
            if(_loc1_ == STAY_1)
            {
               this.m_stay[_loc1_].visible = true;
            }
            else
            {
               this.m_stay[_loc1_].visible = false;
            }
            _loc3_ = 0;
            while(_loc3_ < CCD_STAY_NUM)
            {
               _loc4_ = MovieClip(this.m_stay[_loc1_].getChildByName("mc_bar" + Number(_loc3_ + 1).toString()));
               if(_loc4_)
               {
                  _loc4_.visible = false;
               }
               _loc3_++;
            }
            _loc1_++;
         }
         this.m_gaugeNum = 2;
         var _loc2_:MovieClip = MovieClip(this.m_stay[STAY_1].getChildByName("mc_bar2"));
         if(_loc2_)
         {
            _loc2_.visible = true;
         }
         if(this.m_lifeColMap != null)
         {
            this.m_lifeColMap = null;
            this.m_lifeColMap = new Dictionary();
         }
         this.m_lifeColMap[1] = 1;
         this.m_lifeColMap[2] = 3;
      }
      
      public function UseLifeGauge_1() : *
      {
         var _loc1_:uint = 0;
         while(_loc1_ < this.m_stay.length)
         {
            this.m_stay[_loc1_].visible = false;
            _loc1_++;
         }
         this.m_gaugeNum = 1;
         if(this.m_lifeColMap != null)
         {
            this.m_lifeColMap = null;
            this.m_lifeColMap = new Dictionary();
         }
         this.m_lifeColMap[1] = 1;
      }
      
      public function IsEmpty() : Boolean
      {
         var _loc1_:Boolean = false;
         if(Math.abs(this.m_nowLifeRate - this.m_delayLifeRate) <= CCD_MIN_SUB && this.m_nowLifeRate <= CCD_MIN_SUB)
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function SetLifeGauge(param1:Number) : *
      {
         var _loc7_:* = undefined;
         var _loc8_:MovieClip = null;
         this.SetLifeRateNonDelay(param1);
         var _loc2_:int = 0;
         while(_loc2_ < 4)
         {
            _loc7_ = true;
            if(_loc2_ >= this.m_gaugeNum)
            {
               _loc7_ = false;
            }
            _loc8_ = MovieClip(getChildByName("mc_stay" + _loc2_.toString()));
            if(_loc8_ != null)
            {
               _loc8_.visible = _loc7_;
            }
            _loc2_++;
         }
         var _loc3_:MovieClip = this.GetCurrentLifeGauge();
         var _loc4_:MovieClip = this.GetCurrentDelayGauge();
         var _loc5_:Number = this.GetGaugeFrameRate(this.m_nowLifeRate);
         _loc3_.x = this.m_lifeGaugeBaseX - _loc5_ * _loc3_.width + _loc3_.width;
         this.m_life_eff.mc_l_eff.x = _loc3_.x;
         var _loc6_:Number = this.GetGaugeFrameRate(this.m_delayLifeRate);
         _loc4_.x = this.m_lifeGaugeBaseX - _loc6_ * _loc4_.width + _loc4_.width;
         this.gotoAndStop("lif" + this.m_nowLifeGaugeIdx.toString());
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         this.mc_l_bar1.visible = false;
      }
      
      internal function frame19() : *
      {
         this.mc_l_bar1.visible = true;
      }
      
      internal function frame27() : *
      {
         this.stop();
      }
      
      internal function frame28() : *
      {
         this.mc_l_bar1.visible = false;
      }
      
      internal function frame45() : *
      {
         this.mc_l_bar1.visible = true;
      }
      
      internal function frame53() : *
      {
         this.stop();
      }
      
      internal function frame54() : *
      {
         this.mc_l_bar1.visible = false;
      }
      
      internal function frame71() : *
      {
         this.mc_l_bar1.visible = true;
      }
      
      internal function frame79() : *
      {
         this.stop();
      }
      
      internal function frame80() : *
      {
         this.mc_l_bar1.visible = false;
      }
      
      internal function frame88() : *
      {
         this.stop();
      }
   }
}

