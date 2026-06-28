package
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class anm_check extends MovieClip
   {
      
      public function anm_check()
      {
         super();
         addFrameScript(4,this.frame5);
      }
      
      internal function frame5() : *
      {
         this.stop();
      }
   }
}

