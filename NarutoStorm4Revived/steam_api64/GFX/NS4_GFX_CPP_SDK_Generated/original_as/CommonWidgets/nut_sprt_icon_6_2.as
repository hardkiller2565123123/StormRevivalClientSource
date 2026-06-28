package gauge_sprt_s_fla
{
   import flash.display.MovieClip;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public dynamic class nut_sprt_icon_6 extends MovieClip
   {
      
      public var mc_eff1:MovieClip;
      
      public var mc_gauge:MovieClip;
      
      public var dmy_sprt:nut_tex00;
      
      public var mc_eff_on:MovieClip;
      
      public function nut_sprt_icon_6()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         this.stop();
      }
   }
}

