package script.net_bingo_rslt
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public dynamic class anm_clear extends MovieClip
   {
      
      public var nut_icon_cross:MovieClip;
      
      public function anm_clear()
      {
         super();
         addFrameScript(0,this.frame1,6,this.frame7);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame7() : *
      {
         stop();
      }
   }
}

