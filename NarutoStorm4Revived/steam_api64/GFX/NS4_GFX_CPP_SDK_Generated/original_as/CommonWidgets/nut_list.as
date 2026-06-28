package script.freebtl_top
{
   import flash.display.MovieClip;
   import script.xcmn_eff3.smb_xef_flr1;
   import script.xct_ning1.smb_kni1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class nut_list extends MovieClip
   {
      
      public var mc_kni1:smb_kni1;
      
      public var mc_list:MovieClip;
      
      public var v:smb_xef_flr1;
      
      public function nut_list()
      {
         super();
         addFrameScript(74,this.frame75,94,this.frame95);
      }
      
      internal function frame75() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame95() : *
      {
         stop();
      }
   }
}

