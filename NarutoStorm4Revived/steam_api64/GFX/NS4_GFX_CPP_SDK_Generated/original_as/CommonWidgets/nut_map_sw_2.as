package map_sw_fla
{
   import flash.display.MovieClip;
   import script.xcmn_tex00.nut_tex00;
   import sqript.map_sm.nut_mark;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public dynamic class nut_map_sw_2 extends MovieClip
   {
      
      public var all_mark:nut_mark;
      
      public var dmy_map:nut_tex00;
      
      public var all_posi:MovieClip;
      
      public function nut_map_sw_2()
      {
         super();
         addFrameScript(0,this.frame1,39,this.frame40,64,this.frame65);
      }
      
      internal function frame1() : *
      {
      }
      
      internal function frame40() : *
      {
         this.stop();
      }
      
      internal function frame65() : *
      {
         this.stop();
      }
   }
}

