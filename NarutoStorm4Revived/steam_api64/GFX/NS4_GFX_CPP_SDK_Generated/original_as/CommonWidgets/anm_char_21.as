package start_memory_fla
{
   import flash.display.MovieClip;
   import script.freebtl_course.nut_char_plat_00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol45")]
   public dynamic class anm_char_21 extends MovieClip
   {
      
      public var mc_char1:nut_char_plat_00;
      
      public var mc_char2:nut_char_plat_00;
      
      public var mc_char3:nut_char_plat_00;
      
      public function anm_char_21()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

