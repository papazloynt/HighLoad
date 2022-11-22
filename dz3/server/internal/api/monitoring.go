package api

import (
	"github.com/gofrs/uuid"
	"github.com/labstack/echo/v4"
	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
	"strconv"
	"time"
)

type PrometheusMetrics struct {
	Hits     *prometheus.CounterVec
	Duration *prometheus.HistogramVec
}

func RegisterMonitoring(server *echo.Echo) *PrometheusMetrics {
	var metrics = new(PrometheusMetrics)

	metrics.Hits = prometheus.NewCounterVec(prometheus.CounterOpts{
		Name: "hits",
		Help: "help",
	}, []string{"status", "path", "method"})
	metrics.Duration = prometheus.NewHistogramVec(prometheus.HistogramOpts{
		Name: "duration",
		Help: "help",
	}, []string{"status", "path", "method"})

	prometheus.MustRegister(metrics.Hits, metrics.Duration)

	server.GET("/metrics", echo.WrapHandler(promhttp.Handler()))

	return metrics
}

func (svc *APIService) MetricsMiddleware() echo.MiddlewareFunc {
	return func(next echo.HandlerFunc) echo.HandlerFunc {
		return func(ctx echo.Context) error {
			res := ctx.Response()
			id, _ := uuid.NewV4()

			start := time.Now()
			ctx.Set("REQUEST_ID", id.String())

			if err := next(ctx); err != nil {
				ctx.Error(err)
			}

			responseTime := time.Since(start)

			status := res.Status
			path := ctx.Request().URL.Path
			method := ctx.Request().Method

			svc.metrics.Hits.WithLabelValues(strconv.Itoa(status), path, method).Inc()
			svc.metrics.Duration.WithLabelValues(strconv.Itoa(status), path, method).Observe(responseTime.Seconds())

			return nil
		}
	}
}
