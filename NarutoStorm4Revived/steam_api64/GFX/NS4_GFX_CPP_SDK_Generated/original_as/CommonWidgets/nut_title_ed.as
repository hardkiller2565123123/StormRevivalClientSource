package script.msg_plays
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.xcmn_tex00.nut_tex00;
   import script.xct_stp1.nut_stp1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public class nut_title_ed extends MovieClip
   {
      
      public var all_stp1:nut_stp1;
      
      public var dmy_msg1:nut_tex00;
      
      public var dmy_msg2:nut_tex00;
      
      private var m_txtDmy:MovieClip = null;
      
      private var m_txtDmyFin:MovieClip = null;
      
      private var m_txtLoader:ExtendLoader = null;
      
      private var m_txtLoaderFin:ExtendLoader = null;
      
      public function nut_title_ed()
      {
         super();
         addFrameScript(124,this.frame125,160,this.frame161);
         this.m_txtDmy = this["dmy_msg1"];
         this.m_txtDmyFin = this["dmy_msg2"];
         addEventListener(Event.REMOVED_FROM_STAGE,this.onRemove);
      }
      
      public function onRemove(param1:Event) : *
      {
         if(hasEventListener(Event.ENTER_FRAME) != 0)
         {
            removeEventListener(Event.ENTER_FRAME,this.onLoadCheck);
         }
         if(hasEventListener(Event.ENTER_FRAME) != 0)
         {
            removeEventListener(Event.ENTER_FRAME,this.onLoadCheckFin);
         }
         removeEventListener(Event.REMOVED_FROM_STAGE,this.onRemove);
      }
      
      public function LoadTitle(param1:int) : *
      {
         if(this.m_txtLoader != null)
         {
            this.m_txtDmy.removeChild(this.m_txtLoader);
            if(hasEventListener(Event.ENTER_FRAME) != 0)
            {
               removeEventListener(Event.ENTER_FRAME,this.onLoadCheck);
            }
         }
         if(this.m_txtLoaderFin != null)
         {
            this.m_txtDmyFin.removeChild(this.m_txtLoaderFin);
            if(this.m_txtLoaderFin.contentLoaderInfo.hasEventListener(Event.COMPLETE) != 0)
            {
               this.m_txtLoaderFin.contentLoaderInfo.removeEventListener(Event.COMPLETE,this.onLoadCheckFin);
            }
         }
         this.m_txtLoader = new ExtendLoader();
         this.m_txtLoaderFin = new ExtendLoader();
         this.m_txtDmy.addChild(this.m_txtLoader);
         this.m_txtDmyFin.addChild(this.m_txtLoaderFin);
         var _loc2_:URLRequest = null;
         var _loc3_:URLRequest = null;
         switch(param1)
         {
            case all_nut.CCD_TEXT_MSG_ADV_1:
               _loc2_ = new URLRequest("./LANG/plays_adv1.xfbin");
               _loc3_ = new URLRequest("./LANG/plays_fin.xfbin");
               break;
            case all_nut.CCD_TEXT_MSG_ADV_2:
               _loc2_ = new URLRequest("./LANG/plays_adv2.xfbin");
               _loc3_ = new URLRequest("./LANG/plays_fin.xfbin");
               break;
            case all_nut.CCD_TEXT_MSG_ADV_3:
               _loc2_ = new URLRequest("./LANG/plays_adv3.xfbin");
               _loc3_ = new URLRequest("./LANG/plays_fin.xfbin");
         }
         if(_loc2_ != null)
         {
            this.m_txtLoader.load(_loc2_);
            this.m_txtLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_LEFT);
            addEventListener(Event.ENTER_FRAME,this.onLoadCheck);
            this.m_txtLoaderFin.load(_loc3_);
            this.m_txtLoaderFin.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_RIGHT);
            addEventListener(Event.ENTER_FRAME,this.onLoadCheckFin);
         }
      }
      
      public function onLoadCheck(param1:Event) : *
      {
         if(this.m_txtLoaderFin.IsLoadedAll() == true)
         {
            all_nut(parent).LoadCompleted();
            this.m_txtLoader.contentLoaderInfo.removeEventListener(Event.COMPLETE,this.onLoadCheck);
         }
      }
      
      public function onLoadCheckFin(param1:Event) : *
      {
         if(this.m_txtLoader.IsLoadedAll() == true)
         {
            all_nut(parent).LoadCompleted();
            this.m_txtLoaderFin.contentLoaderInfo.removeEventListener(Event.COMPLETE,this.onLoadCheckFin);
         }
      }
      
      internal function frame125() : *
      {
         this.stop();
      }
      
      internal function frame161() : *
      {
         this.stop();
      }
   }
}

