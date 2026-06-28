package num_time_brt_fla
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol32")]
   public dynamic class anm_time_3 extends MovieClip
   {
      
      public var mc_min1:MovieClip;
      
      public var mc_min10:MovieClip;
      
      public var mc_sec1:MovieClip;
      
      public var mc_sec10:MovieClip;
      
      public function anm_time_3()
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

