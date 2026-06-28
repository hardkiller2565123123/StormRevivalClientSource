package freebtl_top_fla
{
   import flash.display.MovieClip;
   import script.freebtl_top_txt.nut_title_on;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class anm_title_on_eff_5 extends MovieClip
   {
      
      public var all_title_on:nut_title_on;
      
      public function anm_title_on_eff_5()
      {
         super();
         addFrameScript(9,this.frame10);
      }
      
      internal function frame10() : *
      {
         stop();
      }
   }
}

