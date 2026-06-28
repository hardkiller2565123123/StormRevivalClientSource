package start_memory_fla
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol32")]
   public dynamic class all_clear_eff_6 extends MovieClip
   {
      
      public function all_clear_eff_6()
      {
         super();
         addFrameScript(60,this.frame61);
      }
      
      internal function frame61() : *
      {
         stop();
      }
   }
}

