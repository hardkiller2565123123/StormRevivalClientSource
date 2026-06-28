package scrip.modesel
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class nut_event extends MovieClip
   {
      
      public var mc_event:MovieClip;
      
      public function nut_event()
      {
         super();
         addFrameScript(89,this.frame90,92,this.frame93);
      }
      
      internal function frame90() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame93() : *
      {
         this.stop();
      }
   }
}

