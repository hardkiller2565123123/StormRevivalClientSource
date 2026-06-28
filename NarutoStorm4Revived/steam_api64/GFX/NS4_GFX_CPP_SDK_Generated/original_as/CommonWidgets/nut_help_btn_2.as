package help_lang_fla
{
   import flash.display.MovieClip;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class nut_help_btn_2 extends MovieClip
   {
      
      public var dmy_btn:nut_tex00;
      
      public var mc_base:MovieClip;
      
      public function nut_help_btn_2()
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

