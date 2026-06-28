package stagesel_fla
{
   import flash.display.MovieClip;
   import script.stagesel_image.nut_images;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class anm_stage_image00_10 extends MovieClip
   {
      
      public var all_images:nut_images;
      
      public function anm_stage_image00_10()
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

