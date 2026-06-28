package script.stage_logos
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public class storm_one extends MovieClip
   {
      
      public var mc_storm_logo:MovieClip;
      
      public function storm_one()
      {
         super();
         addFrameScript(6,this.frame7,11,this.frame12);
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame12() : *
      {
         stop();
      }
   }
}

