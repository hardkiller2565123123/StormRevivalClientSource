package shop_icrk_fla
{
   import flash.display.MovieClip;
   import script.gauge_icon.nut_status;
   import script.gauge_p.nut_gauge_1p;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol22")]
   public dynamic class nut_gauge_up_7 extends MovieClip
   {
      
      public var all_gauge_1p:nut_gauge_1p;
      
      public var mc_icon1:nut_status;
      
      public var mc_icon2:nut_status;
      
      public var mc_icon3:nut_status;
      
      public var mc_icon4:nut_status;
      
      public var mc_icon5:nut_status;
      
      public var mc_icon6:nut_status;
      
      public function nut_gauge_up_7()
      {
         super();
         addFrameScript(63,this.frame64);
      }
      
      internal function frame64() : *
      {
         this.stop();
      }
   }
}

