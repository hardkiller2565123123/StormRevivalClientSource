package freebtl_top_fla
{
   import flash.display.MovieClip;
   import script.freebtl_top_txt.nut_title_on;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class anm_title_on_4 extends MovieClip
   {
      
      public var all_title_on:nut_title_on;
      
      public var mc_title_on_eff:MovieClip;
      
      public function anm_title_on_4()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
   }
}

