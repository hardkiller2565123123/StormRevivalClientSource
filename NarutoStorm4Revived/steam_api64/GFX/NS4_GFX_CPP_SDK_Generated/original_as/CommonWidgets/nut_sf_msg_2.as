package script.duel_boss_sf
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_sf_msg extends MovieClip
   {
      
      public var dmy_msg:nut_tex00;
      
      public var dmy_msg_eff:nut_tex00;
      
      internal var m_loader:ExtendLoader;
      
      public function nut_sf_msg()
      {
         var dataUrl:URLRequest;
         this.m_loader = new ExtendLoader();
         super();
         addFrameScript(119,this.frame120);
         this.visible = false;
         dataUrl = new URLRequest("LANG/db_sf.xfbin");
         this.m_loader.load(dataUrl);
         this.m_loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_LEFT);
         this.m_loader.contentLoaderInfo.addEventListener(Event.COMPLETE,function(param1:Event):void
         {
            dmy_msg.addChild(m_loader);
         });
      }
      
      public function PlaySecretFactorCutin() : *
      {
         this.visible = true;
         this.gotoAndPlay("in");
      }
      
      internal function frame120() : *
      {
         this.stop();
      }
   }
}

