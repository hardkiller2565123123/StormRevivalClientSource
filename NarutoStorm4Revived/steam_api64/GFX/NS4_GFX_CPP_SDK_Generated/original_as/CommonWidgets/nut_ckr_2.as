package script.gauge_cmn
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol70")]
   public class nut_ckr extends MovieClip
   {
      
      public static const DELAY_GAUGE_SPEED_RATE:* = 0.2;
      
      public static const CHAKRA_GAUGE_DELAY_WAIT:* = 30;
      
      public var mc_oug:MovieClip;
      
      public var mc_limit:MovieClip;
      
      public var mc_ckr_eff:MovieClip;
      
      public var mc_ckr1:MovieClip;
      
      private var m_limit:MovieClip;
      
      private var m_oug:MovieClip;
      
      private var m_ckr_eff:MovieClip;
      
      private var m_ckr1:MovieClip;
      
      public var m_delayChakraRate:Number;
      
      public var m_nowChakraRate:Number;
      
      public var m_spAtkRate:Number;
      
      public var m_delayWait:Number;
      
      public var m_baseX:Number;
      
      public function nut_ckr()
      {
         super();
         this.m_limit = MovieClip(this["mc_limit"]["mc_limit"]);
         this.m_oug = MovieClip(this["mc_oug"]);
         this.m_ckr_eff = MovieClip(this["mc_ckr_eff"]);
         this.m_ckr1 = MovieClip(this["mc_ckr1"]);
         this.SetSpAtkVisible(false);
         removeChild(this.m_ckr_eff);
      }
      
      public function Initialize() : *
      {
         this.m_delayChakraRate = 1;
         this.m_nowChakraRate = 1;
         this.m_spAtkRate = 1;
         this.m_delayWait = 0;
         this.m_baseX = this.m_ckr1.mc_c_bar1.x;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         if(this.m_delayWait > 0)
         {
            --this.m_delayWait;
            if(this.m_delayWait < 0)
            {
               this.m_delayWait = 0;
            }
         }
         else if(this.m_delayChakraRate != this.m_nowChakraRate)
         {
            this.m_delayChakraRate += (this.m_nowChakraRate - this.m_delayChakraRate) * DELAY_GAUGE_SPEED_RATE;
         }
         this.m_ckr1.mc_c_bar1.x = this.m_baseX + this.m_nowChakraRate * this.m_ckr1.mc_c_bar1.width - this.m_ckr1.mc_c_bar1.width;
         this.m_ckr1.mc_cd_bar1.x = this.m_baseX + this.m_delayChakraRate * this.m_ckr1.mc_cd_bar1.width - this.m_ckr1.mc_cd_bar1.width;
         if(this.m_oug)
         {
            if(this.m_nowChakraRate >= this.m_spAtkRate)
            {
               this.m_oug.gotoAndStop("on");
            }
            else
            {
               this.m_oug.gotoAndStop("off");
            }
         }
      }
      
      public function SetChakraRate(param1:Number) : *
      {
         if(this.m_nowChakraRate > param1)
         {
            this.m_delayWait = CHAKRA_GAUGE_DELAY_WAIT;
         }
         this.m_nowChakraRate = param1;
      }
      
      public function SetChakraRateNonDelay(param1:Number) : *
      {
         this.m_nowChakraRate = param1;
         this.m_delayChakraRate = param1;
         this.Update(null);
      }
      
      public function SetChakraEffect(param1:Boolean) : *
      {
         if(param1 == true && this.m_nowChakraRate == 1)
         {
            addChild(this.m_ckr_eff);
         }
         else
         {
            removeChild(this.m_ckr_eff);
         }
      }
      
      public function SetSpAtkRate(param1:Number) : *
      {
         if(this.m_oug)
         {
            this.m_spAtkRate = param1;
            this.m_oug.x = this.m_baseX + this.m_spAtkRate * this.m_ckr1.mc_cd_bar1.width;
         }
      }
      
      public function SetSpAtkVisible(param1:Boolean) : *
      {
         if(this.m_oug)
         {
            this.m_oug.visible = param1;
         }
      }
      
      public function SetChakraLimitRate(param1:Number) : *
      {
         if(this.m_limit)
         {
            this.m_limit.x = param1 * this.m_ckr1.mc_cd_bar1.width - this.m_ckr1.mc_cd_bar1.width;
         }
      }
   }
}

