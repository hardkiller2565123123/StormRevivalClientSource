package script.gauge_cmn
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol87")]
   public class nut_life extends MovieClip
   {
      
      public static const DELAY_GAUGE_SPEED_RATE:* = 0.8;
      
      public static const ONE_GAUGE_VOLUME:* = 0.5;
      
      public static const RED_GAUGE_VOLUME:* = 0.25;
      
      public static const DAMAGE_GAUGE_VISIBLE_FRAME:* = 4;
      
      public var mc_life_eff:MovieClip;
      
      public var mc_life2:MovieClip;
      
      public var mc_life3:MovieClip;
      
      public var mc_life1:MovieClip;
      
      private var m_life_eff:MovieClip;
      
      private var m_life_1:MovieClip;
      
      private var m_life_2:MovieClip;
      
      private var m_life_3:MovieClip;
      
      public var m_nowLifeRate:Number;
      
      public var m_delayLifeRate:Number;
      
      public var m_comboCounter:Number;
      
      public var m_baseX:Number;
      
      public var m_isDirectDamage:Boolean;
      
      public function nut_life()
      {
         super();
         this.m_life_eff = MovieClip(getChildByName("mc_life_eff"));
         this.m_life_1 = MovieClip(getChildByName("mc_life1"));
         this.m_life_2 = MovieClip(getChildByName("mc_life2"));
         this.m_life_3 = MovieClip(getChildByName("mc_life3"));
      }
      
      public function Initialize() : *
      {
         this.m_nowLifeRate = 1;
         this.m_delayLifeRate = 1;
         this.m_comboCounter = 0;
         this.m_baseX = this.m_life_1.mc_l_bar1.x;
         this.m_isDirectDamage = false;
         this.m_life_eff.mc_l_eff.alpha = 0;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:Number = NaN;
         var _loc3_:Number = NaN;
         var _loc4_:Number = NaN;
         var _loc5_:Number = NaN;
         if(this.m_comboCounter <= 0)
         {
            if(this.m_delayLifeRate != this.m_nowLifeRate)
            {
               this.m_delayLifeRate += (this.m_nowLifeRate - this.m_delayLifeRate) * DELAY_GAUGE_SPEED_RATE;
            }
         }
         if(this.m_nowLifeRate > ONE_GAUGE_VOLUME)
         {
            this.m_life_1.mc_l_bar1.visible = true;
            this.m_life_2.mc_l_bar2.x = this.m_baseX;
            this.m_life_3.mc_l_bar3.x = this.m_baseX;
            _loc2_ = (this.m_nowLifeRate - ONE_GAUGE_VOLUME) * 2;
            this.m_life_1.mc_l_bar1.x = this.m_baseX + _loc2_ * this.m_life_1.mc_l_bar1.width - this.m_life_1.mc_l_bar1.width;
            this.m_life_eff.mc_l_eff.x = this.m_life_1.mc_l_bar1.x;
         }
         else
         {
            this.m_life_1.mc_l_bar1.visible = false;
            this.m_life_1.mc_l_bar1.x = this.m_baseX;
            _loc3_ = this.m_nowLifeRate * 2;
            if(this.m_nowLifeRate > RED_GAUGE_VOLUME)
            {
               this.m_life_2.mc_l_bar2.visible = true;
               this.m_life_3.mc_l_bar3.visible = false;
               this.m_life_2.mc_l_bar2.x = this.m_baseX + _loc3_ * this.m_life_2.mc_l_bar2.width - this.m_life_2.mc_l_bar2.width;
               this.m_life_3.mc_l_bar3.x = this.m_baseX;
               this.m_life_eff.mc_l_eff.x = this.m_life_2.mc_l_bar2.x;
            }
            else
            {
               this.m_life_2.mc_l_bar2.visible = false;
               this.m_life_3.mc_l_bar3.visible = true;
               this.m_life_2.mc_l_bar2.x = this.m_baseX;
               this.m_life_3.mc_l_bar3.x = this.m_baseX + _loc3_ * this.m_life_3.mc_l_bar3.width - this.m_life_3.mc_l_bar3.width;
               this.m_life_eff.mc_l_eff.x = this.m_life_3.mc_l_bar3.x;
            }
         }
         if(this.m_delayLifeRate > ONE_GAUGE_VOLUME)
         {
            this.m_life_1.mc_ld_bar1.visible = true;
            this.m_life_2.mc_ld_bar2.x = this.m_baseX;
            this.m_life_3.mc_ld_bar3.x = this.m_baseX;
            _loc4_ = (this.m_delayLifeRate - ONE_GAUGE_VOLUME) * 2;
            this.m_life_1.mc_ld_bar1.x = this.m_baseX + _loc4_ * this.m_life_1.mc_ld_bar1.width - this.m_life_1.mc_ld_bar1.width;
         }
         else
         {
            this.m_life_1.mc_ld_bar1.visible = false;
            this.m_life_1.mc_ld_bar1.x = this.m_baseX;
            _loc5_ = this.m_delayLifeRate * 2;
            if(this.m_nowLifeRate > RED_GAUGE_VOLUME)
            {
               this.m_life_2.mc_ld_bar2.visible = true;
               this.m_life_3.mc_ld_bar3.visible = false;
               this.m_life_2.mc_ld_bar2.x = this.m_baseX + _loc5_ * this.m_life_2.mc_ld_bar2.width - this.m_life_2.mc_ld_bar2.width;
               this.m_life_3.mc_ld_bar3.x = this.m_baseX;
            }
            else
            {
               this.m_life_2.mc_ld_bar2.visible = false;
               this.m_life_3.mc_ld_bar3.visible = true;
               this.m_life_2.mc_ld_bar2.x = this.m_baseX;
               this.m_life_3.mc_ld_bar3.x = this.m_baseX + _loc5_ * this.m_life_3.mc_ld_bar3.width - this.m_life_3.mc_ld_bar3.width;
            }
         }
         if(this.m_life_eff.mc_l_eff.alpha > 0)
         {
            this.m_life_eff.mc_l_eff.alpha -= 0.05;
         }
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
         this.Update(null);
      }
      
      public function SetComboCount(param1:Number) : *
      {
         if(this.m_comboCounter < param1)
         {
            this.m_isDirectDamage = true;
         }
         this.m_comboCounter = param1;
      }
   }
}

