package ELoader
{
   import flash.display.Bitmap;
   import flash.display.Loader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import flash.geom.Matrix;
   import flash.geom.Point;
   import flash.geom.Vector3D;
   import flash.net.URLRequest;
   import flash.system.LoaderContext;
   
   public class ExtendLoader extends Loader
   {
      
      public static const CCD_PIVOT_H_LEFT:uint = 1;
      
      public static const CCD_PIVOT_H_CENTER:uint = 2;
      
      public static const CCD_PIVOT_H_RIGHT:uint = 4;
      
      public static const CCD_PIVOT_V_TOP:uint = 8;
      
      public static const CCD_PIVOT_V_CENTER:uint = 16;
      
      public static const CCD_PIVOT_V_BOTTOM:uint = 32;
      
      public static const CCD_PIVOT_TOP_LEFT:uint = CCD_PIVOT_V_TOP | CCD_PIVOT_H_LEFT;
      
      public static const CCD_PIVOT_TOP_CENTER:uint = CCD_PIVOT_V_TOP | CCD_PIVOT_H_CENTER;
      
      public static const CCD_PIVOT_TOP_RIGHT:uint = CCD_PIVOT_V_TOP | CCD_PIVOT_H_RIGHT;
      
      public static const CCD_PIVOT_CENTER_LEFT:uint = CCD_PIVOT_V_CENTER | CCD_PIVOT_H_LEFT;
      
      public static const CCD_PIVOT_CENTER_CENTER:uint = CCD_PIVOT_V_CENTER | CCD_PIVOT_H_CENTER;
      
      public static const CCD_PIVOT_CENTER_RIGHT:uint = CCD_PIVOT_V_CENTER | CCD_PIVOT_H_RIGHT;
      
      public static const CCD_PIVOT_BOTTOM_LEFT:uint = CCD_PIVOT_V_BOTTOM | CCD_PIVOT_H_LEFT;
      
      public static const CCD_PIVOT_BOTTOM_CENTER:uint = CCD_PIVOT_V_BOTTOM | CCD_PIVOT_H_CENTER;
      
      public static const CCD_PIVOT_BOTTOM_RIGHT:uint = CCD_PIVOT_V_BOTTOM | CCD_PIVOT_H_RIGHT;
      
      private var m_path:String = "";
      
      private var m_context:LoaderContext = null;
      
      private var m_isXfbin:Boolean = false;
      
      private var m_pivot:uint = CCD_PIVOT_TOP_LEFT;
      
      private var m_offset:Vector3D = new Vector3D(0,0,0);
      
      private var m_isCompleted:Boolean = false;
      
      private var m_frameCnt:Number = 0;
      
      private var m_isRequestSmoothing:Boolean = false;
      
      private var m_loadCompleteFunc:Function = null;
      
      public function ExtendLoader()
      {
         super();
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      override public function load(param1:URLRequest, param2:LoaderContext = null) : void
      {
         if(contentLoaderInfo)
         {
            if(contentLoaderInfo.bytesLoaded < contentLoaderInfo.bytesTotal)
            {
               this.close();
            }
            this.unload();
         }
         this.m_path = param1.url;
         this.m_context = param2;
         var _loc3_:* = this.m_path.indexOf(".xfbin");
         if(_loc3_ == -1)
         {
            trace("ExtendLoader[Load request not Xfbin]");
            this.m_isXfbin = false;
         }
         else
         {
            ExternalInterface.call("ScriptLoadXfbin",this,this.m_path);
            this.m_isXfbin = true;
         }
         addEventListener(Event.ENTER_FRAME,this.OnCheckLoaded);
      }
      
      override public function unload() : void
      {
         super.unloadAndStop(true);
         if(this.m_isXfbin == true)
         {
            ExternalInterface.call("ScriptUnloadXfbin",this,this.m_path);
         }
         this.m_path = "";
         this.m_context = null;
         this.m_isXfbin = false;
         this.RemoveCheckloaded();
      }
      
      override public function close() : void
      {
         super.close();
         if(this.m_isXfbin == true)
         {
            ExternalInterface.call("ScriptUnloadXfbin",this,this.m_path);
         }
         this.RemoveCheckloaded();
      }
      
      override public function unloadAndStop(param1:Boolean = true) : void
      {
         super.unloadAndStop(param1);
         if(this.m_isXfbin == true)
         {
            ExternalInterface.call("ScriptUnloadXfbin",this,this.m_path);
         }
         this.m_path = "";
         this.m_context = null;
         this.m_isXfbin = false;
         this.RemoveCheckloaded();
      }
      
      public function IsLoadedXfbin() : Boolean
      {
         var _loc1_:Boolean = true;
         if(this.m_isXfbin == true)
         {
            _loc1_ = Boolean(ExternalInterface.call("ScriptIsLoadedXfbin",this,this.m_path));
         }
         return _loc1_;
      }
      
      public function IsLoadedAll() : Boolean
      {
         return this.m_isCompleted;
      }
      
      public function SetPivot(param1:uint) : *
      {
         this.m_pivot = param1;
         if(this.m_isCompleted == true)
         {
            this.CalcPivot();
         }
      }
      
      public function SetOffset(param1:Number, param2:Number) : *
      {
         this.m_offset.x = param1;
         this.m_offset.y = param2;
         if(this.m_isCompleted == true)
         {
            this.CalcPivot();
         }
      }
      
      public function SetSmoothing(param1:Boolean) : *
      {
         var _loc2_:* = undefined;
         if(this.m_isCompleted == true)
         {
            _loc2_ = Bitmap(content);
            _loc2_.smoothing = param1;
         }
         else
         {
            this.m_isRequestSmoothing = param1;
         }
      }
      
      public function RegistLoadCompleteCallback(param1:Function) : *
      {
         this.m_loadCompleteFunc = param1;
      }
      
      public function ChangeChildToParent(param1:MovieClip, param2:MovieClip) : *
      {
         if(hasEventListener(Event.REMOVED_FROM_STAGE) != 0)
         {
            removeEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
         }
         param2.removeChild(this);
         param1.addChild(this);
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      public function RemoveToParent() : *
      {
         if(hasEventListener(Event.REMOVED_FROM_STAGE) != 0)
         {
            removeEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
         }
         parent.removeChild(this);
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      private function OnCheckLoaded(param1:Event) : *
      {
         var _loc2_:URLRequest = null;
         if(this.IsLoadedXfbin() == true)
         {
            trace("ExtendLoader::CoreLoad[" + this.m_path + "]");
            contentLoaderInfo.addEventListener(Event.COMPLETE,this.OnLoadCompleted);
            _loc2_ = new URLRequest(this.m_path);
            super.load(_loc2_);
            alpha = 0;
            removeEventListener(Event.ENTER_FRAME,this.OnCheckLoaded);
         }
      }
      
      private function RemoveCheckloaded() : *
      {
         if(hasEventListener(Event.ENTER_FRAME) != 0)
         {
            removeEventListener(Event.ENTER_FRAME,this.OnCheckLoaded);
         }
         if(contentLoaderInfo.hasEventListener(Event.COMPLETE) != 0)
         {
            contentLoaderInfo.removeEventListener(Event.COMPLETE,this.OnLoadCompleted);
         }
      }
      
      private function OnRemove(param1:Event) : *
      {
         trace("ExtendLoader::OnRemove");
         this.unload();
         this.RemoveCheckloaded();
         removeEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
      
      private function OnLoadCompleted(param1:Event) : *
      {
         trace("ExtendLoader::OnLoadCompleted");
         this.CalcPivot();
         this.m_frameCnt = 0;
         addEventListener(Event.ENTER_FRAME,this.OnTranslateMatrix);
         contentLoaderInfo.removeEventListener(Event.COMPLETE,this.OnLoadCompleted);
         if(this.m_loadCompleteFunc != null)
         {
            this.m_loadCompleteFunc();
            this.m_loadCompleteFunc = null;
         }
      }
      
      private function OnTranslateMatrix() : *
      {
         var _loc1_:* = undefined;
         trace("ExtendLoader::OnTranslateMatrix");
         alpha = 1;
         this.m_isCompleted = true;
         if(this.m_isRequestSmoothing == true)
         {
            _loc1_ = Bitmap(content);
            _loc1_.smoothing = true;
         }
         removeEventListener(Event.ENTER_FRAME,this.OnTranslateMatrix);
      }
      
      private function CalcPivot() : *
      {
         var _loc1_:Matrix = new Matrix();
         _loc1_.identity();
         var _loc2_:Point = new Point();
         _loc2_.x = 0;
         _loc2_.y = 0;
         if(this.m_pivot & CCD_PIVOT_H_CENTER)
         {
            _loc2_.x = -(width / 2);
         }
         else if(this.m_pivot & CCD_PIVOT_H_RIGHT)
         {
            _loc2_.x = -width;
         }
         if(this.m_pivot & CCD_PIVOT_V_CENTER)
         {
            _loc2_.y = -(height / 2);
         }
         else if(this.m_pivot & CCD_PIVOT_V_BOTTOM)
         {
            _loc2_.y = -height;
         }
         _loc2_.x += this.m_offset.x;
         _loc2_.y += this.m_offset.y;
         _loc1_.translate(_loc2_.x,_loc2_.y);
         transform.matrix = _loc1_;
      }
   }
}

