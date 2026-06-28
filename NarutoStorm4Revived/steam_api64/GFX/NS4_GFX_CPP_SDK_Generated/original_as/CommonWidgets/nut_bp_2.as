package script.result_net
{
   import flash.display.MovieClip;
   import script.net_cmn.smb_win2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class nut_bp extends MovieClip
   {
      
      public var mc_bp_plate:MovieClip;
      
      public var mc_bp_win:smb_win2;
      
      public var txt_bp:MovieClip;
      
      public function nut_bp()
      {
         super();
         addFrameScript(7,this.frame8,14,this.frame15);
      }
      
      internal function frame8() : *
      {
         stop();
      }
      
      internal function frame15() : *
      {
         stop();
      }
   }
}

