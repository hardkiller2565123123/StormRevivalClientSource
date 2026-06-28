package hist_bg_3_c2_fla
{
   import flash.display.MovieClip;
   import script.hist_fade_1.nut_fade_1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class all_nut_1 extends MovieClip
   {
      
      public var mc_fade:nut_fade_1;
      
      public function all_nut_1()
      {
         super();
         addFrameScript(99,this.frame100);
      }
      
      internal function frame100() : *
      {
         this.stop();
      }
   }
}

