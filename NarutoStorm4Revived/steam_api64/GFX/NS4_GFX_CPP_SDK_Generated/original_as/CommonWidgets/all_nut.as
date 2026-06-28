package script.collect_skill
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public dynamic class all_nut extends MovieClip
   {
      
      public var all_use:nut_use;
      
      public function all_nut()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

